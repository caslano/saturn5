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
+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
*/