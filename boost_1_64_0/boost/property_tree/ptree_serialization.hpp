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
JvC/+PnCd9FrQ/xsJ946Ge8e7RyO89Jb++JPD4g3H/PjbP7k/WuPN44zrzx52/H8NYN/zFPX7c2+p7DTz+DFWv1hODIBvkzaE/9OYHSdzvHvqewSVxL0tdX9DsFnPLVgpv1/Of6+N/5eBO/xu65T2W01XPwL/7tO3uDcdp7+eDN9zO792G+G6/4VPuKjWR/iX0n+djucl+8WjsTLOsHPofwWL5/6mzyvn+sOpxfnOSvF9/Ud8f2v7X93+XYGflk7pa+ZHo1X85Ma73OOrek4caCjfAqOJBuwn+/4z7Xi6Hh6PA++xnUb/lWnZTRWv6i+sjyhDi1e8qMxx7hfffiyVl5RW9/9ZXbr3HU9vKvZF/7ub//20tOX4t8ccfg8dnlpmvNl+k5JfjwZ3uELRRcn1dnYwWP43Ao8Un6W5E/rc9SD6CX3KvwiPjc/WZ9iC/3K70ecj1/Vp9df4/Pe9BR/j6IYL0x3TlV/L/WsvLRSPq++NOxYfHEwnqZ/NawAHzoPbsbPKRspDsffS2yS5rwkfrVKfzzHvo7BJ8/Fa56Slw+Ho2ckovd5ftBuuFhxpTzj2mjc+5FzRDvZkTp2/sokfJFPb8G7s8x7fRq/xnudC8+Xt066FH62sH/W31k9al5Kv4OdzzukzgrPM/3/pJPwiv/ACfFk9gS4fab9WwqHP4zGymvhw7nyoUNJPJZ9D7VP/LLaedGVp4vDeHJmmfzC2H2gfOFM+/FpNGbhFUVl4ksz7/uNXZ8uv2ZXBS3gcQt63ok3PUJfsX94Tn8yA27TU/VB7xsQP9chEc3jTfs8wLyPMb8j4XBKfvAOvBZXlsc4Yd+qr5CP6J83/lp9OsZncWf6VSnzTvh/5zM+hk+34SnOo0ztgqf9wg5+8fpwdvonvOdvPW+y3+nqV54fWUoP2Q8kfb8UbtB3dprzEznO67yLZ+DnKXayfBi7g2vNZuOP5lGejTe2jMbinvxfvjjpZLgvv+v+F+t+n/0l4ad8panzCaVv2A/7kHuruvPV8Oxmech++n4IT70vGouGsdfn+OMD8ffW4VUdcaBSX2OgfY2/1wXXWuM1Bb/gFfhy4XZ5y0X8bAM+9TO/f4C/ny1PeQHPfRIfcY6k+k555NX4yyFxAZ/vvJYfqCNV7GaXo/FF5wDq7BOPvxJfH4bjZ8CVnvTtPqk85wLnqvu0j3FZPJ+S7lwJfMt1Xlndunh2fH6CPvhRpXjd8C/ywWbyQbx7gT5flftsHik+zsOnT6aHDtbT133x+dQ/2f3d7LVEHkYPW41V+ra5V3j/MLzlVfmTccxydZ8u7PR5eMLeRgyBwxuiMetK69FXXfpHNJY1sR+d8MYPYvukjyR/bCjOqS+vXW2fT4BXV+p/5eiffuec3X3yyY7J6PWTxG04tvpZ+aFxwUBxpzE7Pd667VM99xnRSV42kF+fH43XDNn9/uMPL65Z/Me3NeU/HN5/7f4HD9bsr9lTXbNz8aL2+9++97udNe3fnz3k25rL9gwesnfj4sP7izdW/zS7emBN3+9fq7m+asD+mpp3Fx2s2L/ynQE1Pxyuqb6gpmpgRdudn2ysqX6wZnJNZVb7xQe7/7n1+41DFq4pH/To/pqdixZvGzK5oGbnoR+qaxaH+zz408KNNffs3zhkdlXVBUNqSvctLl/+/v41F+4vrxn085C5NXfk9f3qYM3P+2et+WBywb492x59/OD+SUMuG3Jwcs3Omh1/llc/9sPmjdXPLP65ZuGibw5vG7Lo15+/PVzzUOVXL2z4c3/NI0NeK+pZ/tjg8gUT2y+ufvOxbYdvbL9/x8GqxecvfLx7TWXNuWv63nn74TU/1Oxb9EP1HxU1O98ddHw=
*/