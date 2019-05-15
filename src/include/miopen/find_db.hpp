/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef GUARD_MIOPEN_FIND_DB_HPP_
#define GUARD_MIOPEN_FIND_DB_HPP_

#include <miopen/db.hpp>
#include <miopen/db_path.hpp>
#include <miopen/db_record.hpp>
#include <miopen/env.hpp>
#include <miopen/perf_field.hpp>

#include <boost/optional.hpp>

#include <functional>
#include <vector>

MIOPEN_DECLARE_ENV_VAR(MIOPEN_DEBUG_DISABLE_FIND_DB)

namespace miopen {

struct Handle;

class FindDb
{
    public:
    static bool enabled;                                  // For unit tests.
    static boost::optional<std::string>& path_override(); /// \todo Remove when #1723 is resolved.

    template <class TProblemDescription>
    static std::vector<PerfField> TryLoad(Handle& handle,
                                          const TProblemDescription& problem,
                                          const std::function<void(DbRecord&)>& regenerator)
    {
        auto ret     = std::vector<PerfField>{};
        auto find_db = FindDb{handle, problem};

        if(find_db.loaded && !find_db.CopyValidating(handle, ret))
            return ret;

        MIOPEN_LOG_I("Find-db regenerating.");
        ret.clear();
        find_db.loaded = false;
        find_db.record.emplace(problem);
        regenerator(*find_db.record);

        for(const auto& pair : find_db.record->As<FindDbData>())
            // cppcheck-suppress useStlAlgorithm
            ret.push_back(
                {pair.first, pair.second.solver_id, pair.second.time, pair.second.workspace});

        return ret;
    }

    FindDb(const FindDb&) = delete;
    FindDb& operator=(const FindDb&) = delete;

    private:
    std::string path;
    boost::optional<DbTimer<Db>> db;
    boost::optional<DbRecord> record{boost::none};
    bool loaded = false;

    FindDb(FindDb&&) = default;
    FindDb& operator=(FindDb&&) = default;

    template <class TProblemDescription>
    FindDb(Handle& handle, const TProblemDescription& problem)
        : path(path_override() ? *path_override() : GetPath(handle)), db(TryLoadDb(path))
    {
        if(!db.is_initialized())
            return;

        record = db->FindRecord(problem);
        loaded = record.is_initialized();
    }

    ~FindDb()
    {
        if(!db.is_initialized() || !record.is_initialized() || loaded)
            return;
        if(!db->StoreRecord(record.get()))
            MIOPEN_LOG_E("Failed to store record to find-db at <" << path << ">");
    }

    static std::string GetPath(Handle& handle);

    static boost::optional<DbTimer<Db>> TryLoadDb(const std::string& path)
    {
        if(!enabled || IsEnabled(MIOPEN_DEBUG_DISABLE_FIND_DB{}))
            return boost::none;
        return DbTimer<Db>{{path, false}};
    }

    // Returns true if rebuild is required
    bool CopyValidating(Handle& handle, std::vector<PerfField>& to) const;
};

} // namespace miopen

#endif
