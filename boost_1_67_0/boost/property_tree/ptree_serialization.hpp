// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_SERIALIZATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_SERIALIZATION_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace property_tree
{

    ///////////////////////////////////////////////////////////////////////////
    // boost::serialization support

    /**
     * Serialize the property tree to the given archive.
     * @note In addition to serializing to regular archives, this supports
     *       serializing to archives requiring name-value pairs, e.g. XML
     *       archives.  However, the output format in the XML archive is not
     *       guaranteed to be the same as that when using the Boost.PropertyTree
     *       library's @c boost::property_tree::xml_parser::write_xml.
     * @param ar The archive to which to save the serialized property tree.
     *           This archive should conform to the concept laid out by the
     *           Boost.Serialization library.
     * @param t The property tree to serialize.
     * @param file_version file_version for the archive.
     * @post @c ar will contain the serialized form of @c t.
     */
    template<class Archive, class K, class D, class C>
    inline void save(Archive &ar,
                     const basic_ptree<K, D, C> &t,
                     const unsigned int file_version)
    {
        using namespace boost::serialization;
        stl::save_collection<Archive, basic_ptree<K, D, C> >(ar, t);
        ar << make_nvp("data", t.data());
    }

    namespace detail
    {
        template <class Archive, class K, class D, class C>
        inline void load_children(Archive &ar,
                                  basic_ptree<K, D, C> &t)
        {
            namespace bsl = boost::serialization;
            namespace bsa = boost::archive;

            typedef basic_ptree<K, D, C> tree;
            typedef typename tree::value_type value_type;
    
            bsl::collection_size_type count;
            ar >> BOOST_SERIALIZATION_NVP(count);
            bsl::item_version_type item_version(0);
            const bsa::library_version_type library_version(
                ar.get_library_version()
            );
            if(bsa::library_version_type(3) < library_version){
                ar >> BOOST_SERIALIZATION_NVP(item_version);
            }
            // Can't use the serialization helper, it expects resize() to exist
            // for default-constructible elements.
            // This is a copy/paste of the fallback version.
            t.clear();
            while(count-- > 0){
                bsl::detail::stack_construct<Archive, value_type>
                    u(ar, item_version);
                ar >> bsl::make_nvp("item", u.reference());
                t.push_back(u.reference());
                ar.reset_object_address(& t.back() , & u.reference());
            }
        }
    }

    /**
     * De-serialize the property tree to the given archive.
     * @note In addition to de-serializing from regular archives, this supports
     *       loading from archives requiring name-value pairs, e.g. XML
     *       archives. The format should be that used by
     *       boost::property_tree::save.
     * @param ar The archive from which to load the serialized property tree.
     *           This archive should conform to the concept laid out by the
     *           Boost.Serialization library.
     * @param t The property tree to de-serialize.
     * @param file_version file_version for the archive.
     * @post @c t will contain the de-serialized data from @c ar.
     */
    template<class Archive, class K, class D, class C>
    inline void load(Archive &ar,
                     basic_ptree<K, D, C> &t,
                     const unsigned int file_version)
    {
        namespace bsl = boost::serialization;

        detail::load_children(ar, t);
        ar >> bsl::make_nvp("data", t.data());
    }

    /**
     * Load or store the property tree using the given archive.
     * @param ar The archive from which to load or save the serialized property
     *           tree. The type of this archive will determine whether saving or
     *           loading is performed.
     * @param t The property tree to load or save.
     * @param file_version file_version for the archive.
     */
    template<class Archive, class K, class D, class C>
    inline void serialize(Archive &ar,
                          basic_ptree<K, D, C> &t,
                          const unsigned int file_version)
    {
        using namespace boost::serialization;
        split_free(ar, t, file_version);
    }

} }

#endif

/* ptree_serialization.hpp
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
*/