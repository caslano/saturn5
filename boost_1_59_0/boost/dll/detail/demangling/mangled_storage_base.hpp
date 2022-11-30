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
+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
*/