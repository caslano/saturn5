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
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
*/