//  Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_MANGLE_STORAGE_BASE_HPP_
#define BOOST_DLL_DETAIL_MANGLE_STORAGE_BASE_HPP_

#include <vector>
#include <string>
#include <map>
#include <boost/dll/detail/demangling/demangle_symbol.hpp>
#include <boost/dll/library_info.hpp>
#include <boost/type_index/ctti_type_index.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace dll { namespace detail {

///stores the mangled names with the demangled name.
struct mangled_storage_base
{
    struct entry
    {
        std::string mangled;
        std::string demangled;
        entry() = default;
        entry(const std::string & m, const std::string &d) : mangled(m), demangled(d) {}
        entry(const entry&) = default;
        entry(entry&&)         = default;
        entry &operator= (const entry&) = default;
        entry &operator= (entry&&)         = default;
    };
protected:
    std::vector<entry> storage_;
    ///if a unknown class is imported it can be overloaded by this type
    std::map<boost::typeindex::ctti_type_index, std::string> aliases_;
public:
    void assign(const mangled_storage_base & storage)
    {
        aliases_  = storage.aliases_;
        storage_  = storage.storage_;
    }
    void swap( mangled_storage_base & storage)
    {
        aliases_.swap(storage.aliases_);
        storage_.swap(storage.storage_);
    }
    void clear()
    {
        storage_.clear();
        aliases_.clear();
    }
    std::vector<entry> & get_storage() {return storage_;};
    template<typename T>
    std::string get_name() const
    {
        using boost::typeindex::ctti_type_index;
        auto tx = ctti_type_index::type_id<T>();
        auto val = (aliases_.count(tx) > 0) ? aliases_.at(tx) : tx.pretty_name();
        return val;
    }

    mangled_storage_base() = default;
    mangled_storage_base(mangled_storage_base&&) = default;
    mangled_storage_base(const mangled_storage_base&) = default;

    mangled_storage_base(const std::vector<std::string> & symbols) { add_symbols(symbols);}

    explicit mangled_storage_base(library_info & li) : mangled_storage_base(li.symbols()) {}

    explicit mangled_storage_base(
            const boost::dll::fs::path& library_path,
            bool throw_if_not_native_format = true)
        : mangled_storage_base(library_info(library_path, throw_if_not_native_format).symbols())
    {

    }

    void load(library_info & li) { storage_.clear(); add_symbols(li.symbols()); };
    void load(const boost::dll::fs::path& library_path,
            bool throw_if_not_native_format = true)
    {
        storage_.clear();
        add_symbols(library_info(library_path, throw_if_not_native_format).symbols());
    };

    /*! Allows do add a class as alias, if the class imported is not known
     * in this binary.
     * @tparam Alias The Alias type
     *  @param The name to create the alias for.
     *
     *  @note There can be multiple aliases, this is on purpose.
     */
    template<typename Alias> void add_alias(const std::string& name)
    {
        aliases_.emplace(
            boost::typeindex::ctti_type_index::type_id<Alias>(),
            name
            );
    }
    void add_symbols(const std::vector<std::string> & symbols)
    {
        for (auto & sym : symbols)
        {
            auto dm = demangle_symbol(sym);
            if (!dm.empty())
                storage_.emplace_back(sym, dm);
            else
                storage_.emplace_back(sym, sym);
        }
    }


};


}}}

#endif /* BOOST_DLL_DETAIL_MANGLE_STORAGE_HPP_ */

/* mangled_storage_base.hpp
9IPt4fV6eijx+D9Iv0DLI/LD3rxSZZm/wLSwuXEu0MY25X8U8lue8CoW+uazHS4NbNIn3D3Jz5b+GQ5IuQTpHCekxTZIuRJSIUDaewM+8X3NB3Nc7mvG9KuItxziuK+5Fjc0aczpOH6ZiEfC2O9rfvNLbdx+R/PMXuT4YU9uZV7Tc69cwkyN2y5h3qW3/M5+jkuY92frLS/k+Buy9ZYXcfyPP1PLiznm3GyyhUjqGlXCq5Y39Pid3axEebGPPh/dpuLo3urQuJ+hXoPwr/OZ/TPwlsjGkTtRT4hHgIXGvM62uzu4SsS3Icljz2J66rz+FEXCPkBJ95imX4Ap29Zu5NcIKV0r9Rx+w5Foauqmsp2pfTdZDilu94jzYXptqxVkE89twR8sMRT++ivmehhZY7HYYyHTuJCqo4mt4arl7I45u5vHcc7BiXL2wJw9zF6cM5AoZ0/M2dP8cT+Vc4STUrm9cCDCXqoPBAarQBdcS1WgNQRGUIAJ8VcIYenqnW3xgK96V3qralzEqnc1a1XdCvJL7wM54K0eau4VV6aw9MZVRGIQoSy++rL410Ge+gD0K9uYugT+1MwAIQrDe4UJ/oo/V1X0xJ689ES2sgPpYFnAiB4nvpSdcDBU7pGLUdh89qvaOB+FXyyP67NFfgtIBNctdXzdPJaWjA67jv4eAfkIJn0Gvdp3gfY9Gb83N3Z9KRLn3z3UpA9CkKeaMnRg0wyUd8oNbLj4FKSBEDk+n4dxWWq6h1GtULZ7ZMlAnK5CC5KN2TzzumM2Vj9wvpZavicEHzZKWiuRtmZ6ikAnwIqVgMgakB6ChWeIihs91k0ImIg07ygoxq1KQQuP01vxfAcpcnCcqxPz7DtSYY0YWZLOaNGpSLYxrytOWcXBolahTVQoO2WeFXcfxCH8rwi+NEohRYwO5Qxx4HKRVbCEgGVFLm4JcRFl7TKAHLLv6iGsXU7pCdYu3UB4wiyQIpy7Z0mygrULqlZYB0VHOlEhvbOjnVLzl8/FUO5HaiusFDj/RS1xQiNn1dryvlT0QLF+feH6HgpC8k23XD2eOlbfg9WMAxZBg2QmVg/sHRjciU5UZjWASkuFSuyURHjE2tBrKVbW/iKiJFNUX9JcdGEJJofEvPThl0EtE+481O0YoZbwiXFO8xh55r7YJv5mP6fWaPgBgivkVRVKTXmAFEhnRxo0NRQ/DdQX3SSoM8laq3tWO4OAvTbIaVbntP9TRc+goh8d2M5YX4gpX5u1VLRB/llubHaRdzIF/++mWJ9PjoJcyOYVUoa3zEzFAIwZr+Ff6gEehJ+p/is/NRzv5uSQFpWeiGGvRW4O9zGaNKve7HIvqErblu08Eq9dtU4/oB09ooawFqcIdirX2yyRM13lfL9bAzmbqZxV9edU2ZbVk60mlqix0AKkR0rJgSrZoyXjO6filq+zndndkm3nD/snzok1e8RETh+JE7mLveFPQ1F5qzkdypFAmL7YZ4MhAluMkbZIHDAkXvrUOWSq2GTW1MA1ZFnEwFww+DJ/x9zAVd6Z3oWNQm3CzvjEws5TXTXDT4zZ4vXw2YY92nAXgRoh9LjLP0FvLgs6hlP+2dwYeScs7n92Zv0pCzaFBFg8pngJHjfPV95Fy0q9kUvEgqJW4cuIFU3qKlbhK+GPeQMcO2AWj2q5kJrLW5QHvX2rh8MiMi+Ii3Mx7Z+ntCCNaAW8FyFPLorMtuP8kmhGqsopbSNrvvYoZPAh0efdKkERBavITlwF3I3yG5ynyFqhi+R6WozrqVJlRdRoiITK87x8g+7+zjQcWGRmsYM1KdZ+aIvRsu4miaZPFkQtZyVnBNowFCr2X7laOljOhdX7Ev/ly1U=
*/