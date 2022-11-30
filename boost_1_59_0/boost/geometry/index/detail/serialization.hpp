// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_SERIALIZATION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_SERIALIZATION_HPP

#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>

//#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
//#include <boost/serialization/nvp.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/parameters.hpp>
#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>

// TODO
// how about using the unsigned type capable of storing Max in compile-time versions?

// TODO
// - add wrappers for Point and Box and implement serialize for those wrappers instead of
//   raw geometries
//   PROBLEM: after implementing this, how Values would be set?
// - store the name of the parameters to know how to load and detect errors
// - in the header, once store info about the Indexable and Bounds types (geometry type, point CS, Dim, etc.)
//   each geometry save without this info

// TODO - move to index/detail/serialization.hpp
namespace boost { namespace geometry { namespace index {

// Forward declaration
template <typename Value, typename Options, typename IndexableGetter, typename EqualTo, typename Allocator>
class rtree;

namespace detail {

// TODO - use boost::move?
template<typename T>
class serialization_storage
{
public:
    template <typename Archive>
    serialization_storage(Archive & ar, unsigned int version)
    {
        boost::serialization::load_construct_data_adl(ar, this->address(), version);
    }
    ~serialization_storage()
    {
        this->address()->~T();
    }
    T * address()
    {
        return static_cast<T*>(m_storage.address());
    }
private:
    boost::aligned_storage<sizeof(T), boost::alignment_of<T>::value> m_storage;
};

// TODO - save and load item_version? see: collections_load_imp and collections_save_imp
// this should be done once for the whole container
// versions of all used types should be stored

template <typename T, typename Archive> inline
T serialization_load(const char * name, Archive & ar)
{
    namespace bs = boost::serialization;    
    serialization_storage<T> storage(ar, bs::version<T>::value);        // load_construct_data
    ar >> boost::serialization::make_nvp(name, *storage.address());   // serialize
    //ar >> *storage.address();                                           // serialize
    return *storage.address();
}

template <typename T, typename Archive> inline
void serialization_save(T const& t, const char * name, Archive & ar)
{
    namespace bs = boost::serialization;
    bs::save_construct_data_adl(ar, boost::addressof(t), bs::version<T>::value);  // save_construct_data
    ar << boost::serialization::make_nvp(name, t);                                // serialize
    //ar << t;                                                                      // serialize
}
    
}}}}

// TODO - move to index/serialization/rtree.hpp
namespace boost { namespace serialization {

// boost::geometry::index::linear

template<class Archive, size_t Max, size_t Min>
void save_construct_data(Archive & ar, const boost::geometry::index::linear<Max, Min> * params, unsigned int )
{
    size_t max = params->get_max_elements(), min = params->get_min_elements();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
}
template<class Archive, size_t Max, size_t Min>
void load_construct_data(Archive & ar, boost::geometry::index::linear<Max, Min> * params, unsigned int )
{
    size_t max, min;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    if ( max != params->get_max_elements() || min != params->get_min_elements() )
        // TODO change exception type
        BOOST_THROW_EXCEPTION(std::runtime_error("parameters not compatible"));
    // the constructor musn't be called for this type
    //::new(params)boost::geometry::index::linear<Max, Min>();
}
template<class Archive, size_t Max, size_t Min> void serialize(Archive &, boost::geometry::index::linear<Max, Min> &, unsigned int) {}

// boost::geometry::index::quadratic

template<class Archive, size_t Max, size_t Min>
void save_construct_data(Archive & ar, const boost::geometry::index::quadratic<Max, Min> * params, unsigned int )
{
    size_t max = params->get_max_elements(), min = params->get_min_elements();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
}
template<class Archive, size_t Max, size_t Min>
void load_construct_data(Archive & ar, boost::geometry::index::quadratic<Max, Min> * params, unsigned int )
{
    size_t max, min;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    if ( max != params->get_max_elements() || min != params->get_min_elements() )
        // TODO change exception type
        BOOST_THROW_EXCEPTION(std::runtime_error("parameters not compatible"));
    // the constructor musn't be called for this type
    //::new(params)boost::geometry::index::quadratic<Max, Min>();
}
template<class Archive, size_t Max, size_t Min> void serialize(Archive &, boost::geometry::index::quadratic<Max, Min> &, unsigned int) {}

// boost::geometry::index::rstar

template<class Archive, size_t Max, size_t Min, size_t RE, size_t OCT>
void save_construct_data(Archive & ar, const boost::geometry::index::rstar<Max, Min, RE, OCT> * params, unsigned int )
{
    size_t max = params->get_max_elements()
         , min = params->get_min_elements()
         , re = params->get_reinserted_elements()
         , oct = params->get_overlap_cost_threshold();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
    ar << boost::serialization::make_nvp("re", re);
    ar << boost::serialization::make_nvp("oct", oct);
}
template<class Archive, size_t Max, size_t Min, size_t RE, size_t OCT>
void load_construct_data(Archive & ar, boost::geometry::index::rstar<Max, Min, RE, OCT> * params, unsigned int )
{
    size_t max, min, re, oct;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    ar >> boost::serialization::make_nvp("re", re);
    ar >> boost::serialization::make_nvp("oct", oct);
    if ( max != params->get_max_elements() || min != params->get_min_elements() ||
         re != params->get_reinserted_elements() || oct != params->get_overlap_cost_threshold() )
        // TODO change exception type
        BOOST_THROW_EXCEPTION(std::runtime_error("parameters not compatible"));
    // the constructor musn't be called for this type
    //::new(params)boost::geometry::index::rstar<Max, Min, RE, OCT>();
}
template<class Archive, size_t Max, size_t Min, size_t RE, size_t OCT>
void serialize(Archive &, boost::geometry::index::rstar<Max, Min, RE, OCT> &, unsigned int) {}

// boost::geometry::index::dynamic_linear

template<class Archive>
inline void save_construct_data(Archive & ar, const boost::geometry::index::dynamic_linear * params, unsigned int )
{
    size_t max = params->get_max_elements(), min = params->get_min_elements();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
}
template<class Archive>
inline void load_construct_data(Archive & ar, boost::geometry::index::dynamic_linear * params, unsigned int )
{
    size_t max, min;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    ::new(params)boost::geometry::index::dynamic_linear(max, min);
}
template<class Archive> void serialize(Archive &, boost::geometry::index::dynamic_linear &, unsigned int) {}

// boost::geometry::index::dynamic_quadratic

template<class Archive>
inline void save_construct_data(Archive & ar, const boost::geometry::index::dynamic_quadratic * params, unsigned int )
{
    size_t max = params->get_max_elements(), min = params->get_min_elements();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
}
template<class Archive>
inline void load_construct_data(Archive & ar, boost::geometry::index::dynamic_quadratic * params, unsigned int )
{
    size_t max, min;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    ::new(params)boost::geometry::index::dynamic_quadratic(max, min);
}
template<class Archive> void serialize(Archive &, boost::geometry::index::dynamic_quadratic &, unsigned int) {}

// boost::geometry::index::dynamic_rstar

template<class Archive>
inline void save_construct_data(Archive & ar, const boost::geometry::index::dynamic_rstar * params, unsigned int )
{
    size_t max = params->get_max_elements()
         , min = params->get_min_elements()
         , re = params->get_reinserted_elements()
         , oct = params->get_overlap_cost_threshold();
    ar << boost::serialization::make_nvp("max", max);
    ar << boost::serialization::make_nvp("min", min);
    ar << boost::serialization::make_nvp("re", re);
    ar << boost::serialization::make_nvp("oct", oct);
}
template<class Archive>
inline void load_construct_data(Archive & ar, boost::geometry::index::dynamic_rstar * params, unsigned int )
{
    size_t max, min, re, oct;
    ar >> boost::serialization::make_nvp("max", max);
    ar >> boost::serialization::make_nvp("min", min);
    ar >> boost::serialization::make_nvp("re", re);
    ar >> boost::serialization::make_nvp("oct", oct);
    ::new(params)boost::geometry::index::dynamic_rstar(max, min, re, oct);
}
template<class Archive> void serialize(Archive &, boost::geometry::index::dynamic_rstar &, unsigned int) {}

}} // boost::serialization

// TODO - move to index/detail/serialization.hpp or maybe geometry/serialization.hpp
namespace boost { namespace geometry { namespace index { namespace detail {

template <typename P, size_t I = 0, size_t D = geometry::dimension<P>::value>
struct serialize_point
{
    template <typename Archive>
    static inline void save(Archive & ar, P const& p, unsigned int version)
    {
        typename coordinate_type<P>::type c = get<I>(p);
        ar << boost::serialization::make_nvp("c", c);
        serialize_point<P, I+1, D>::save(ar, p, version);
    }

    template <typename Archive>
    static inline void load(Archive & ar, P & p, unsigned int version)
    {
        typename geometry::coordinate_type<P>::type c;
        ar >> boost::serialization::make_nvp("c", c);
        set<I>(p, c);
        serialize_point<P, I+1, D>::load(ar, p, version);
    }
};

template <typename P, size_t D>
struct serialize_point<P, D, D>
{
    template <typename Archive> static inline void save(Archive &, P const&, unsigned int) {}
    template <typename Archive> static inline void load(Archive &, P &, unsigned int) {}
};

}}}}

// TODO - move to index/detail/serialization.hpp or maybe geometry/serialization.hpp
namespace boost { namespace serialization {

template<class Archive, typename T, size_t D, typename C>
void save(Archive & ar, boost::geometry::model::point<T, D, C> const& p, unsigned int version)
{
    boost::geometry::index::detail::serialize_point< boost::geometry::model::point<T, D, C> >::save(ar, p, version);
}
template<class Archive, typename T, size_t D, typename C>
void load(Archive & ar, boost::geometry::model::point<T, D, C> & p, unsigned int version)
{
    boost::geometry::index::detail::serialize_point< boost::geometry::model::point<T, D, C> >::load(ar, p, version);
}
template<class Archive, typename T, size_t D, typename C>
inline void serialize(Archive & ar, boost::geometry::model::point<T, D, C> & o, const unsigned int version) { split_free(ar, o, version); }

template<class Archive, typename P>
inline void serialize(Archive & ar, boost::geometry::model::box<P> & b, const unsigned int)
{
    ar & boost::serialization::make_nvp("min", b.min_corner());
    ar & boost::serialization::make_nvp("max", b.max_corner());
}

}} // boost::serialization

// TODO - move to index/detail/rtree/visitors/save.hpp
namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace visitors {

// TODO move saving and loading of the rtree outside the rtree, this will require adding some kind of members_view

template <typename Archive, typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class save
    : public rtree::visitor<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag, true>::type
{
public:
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type leaf;

    save(Archive & archive, unsigned int version)
        : m_archive(archive), m_version(version)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // CONSIDER: change to elements_type::size_type or size_type
        // or use fixed-size type like uint32 or even uint16?
        size_t s = elements.size();
        m_archive << boost::serialization::make_nvp("s", s);

        for (typename elements_type::const_iterator it = elements.begin() ; it != elements.end() ; ++it)
        {
            serialization_save(it->first, "b", m_archive);

            rtree::apply_visitor(*this, *it->second);
        }
    }

    inline void operator()(leaf const& l)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        //typedef typename elements_type::size_type elements_size;
        elements_type const& elements = rtree::elements(l);

        // CONSIDER: change to elements_type::size_type or size_type
        // or use fixed-size type like uint32 or even uint16?
        size_t s = elements.size();
        m_archive << boost::serialization::make_nvp("s", s);

        for (typename elements_type::const_iterator it = elements.begin() ; it != elements.end() ; ++it)
        {
            serialization_save(*it, "v", m_archive);
        }
    }

private:
    Archive & m_archive;
    unsigned int m_version;
};

}}}}}} // boost::geometry::index::detail::rtree::visitors

// TODO - move to index/detail/rtree/load.hpp
namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree {

template <typename MembersHolder>
class load
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::node_pointer node_pointer;
    typedef typename allocators_type::size_type size_type;

    typedef rtree::subtree_destroyer<MembersHolder> subtree_destroyer;

public:
    template <typename Archive> inline static
    node_pointer apply(Archive & ar, unsigned int version, size_type leafs_level,
                       size_type & values_count,
                       parameters_type const& parameters,
                       translator_type const& translator,
                       allocators_type & allocators)
    {
        values_count = 0;
        return raw_apply(ar, version, leafs_level, values_count, parameters, translator, allocators);
    }

private:
    template <typename Archive> inline static
    node_pointer raw_apply(Archive & ar, unsigned int version, size_type leafs_level,
                           size_type & values_count,
                           parameters_type const& parameters,
                           translator_type const& translator,
                           allocators_type & allocators,
                           size_type current_level = 0)
    {
        //BOOST_GEOMETRY_INDEX_ASSERT(current_level <= leafs_level, "invalid parameter");

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        //typedef typename elements_type::size_type elements_size;

        // CONSIDER: change to elements_type::size_type or size_type
        // or use fixed-size type like uint32 or even uint16?
        size_t elements_count;
        ar >> boost::serialization::make_nvp("s", elements_count);

        // root may contain count < min but shouldn't contain count > max
        if ( (elements_count < parameters.get_min_elements() && current_level > 0)
                || parameters.get_max_elements() < elements_count )
        {
            BOOST_THROW_EXCEPTION(std::runtime_error("rtree loading error"));
        }

        if ( current_level < leafs_level )
        {
            node_pointer n = rtree::create_node<allocators_type, internal_node>::apply(allocators);         // MAY THROW (A)
            subtree_destroyer auto_remover(n, allocators);    
            internal_node & in = rtree::get<internal_node>(*n);

            elements_type & elements = rtree::elements(in);

            elements.reserve(elements_count);                                                               // MAY THROW (A)

            for ( size_t i = 0 ; i < elements_count ; ++i )
            {
                typedef typename elements_type::value_type::first_type box_type;
                box_type b = serialization_load<box_type>("b", ar);
                node_pointer n = raw_apply(ar, version, leafs_level, values_count, parameters, translator, allocators, current_level+1); // recursive call
                elements.push_back(element_type(b, n));
            }

            auto_remover.release();
            return n;
        }
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(current_level == leafs_level, "unexpected value");

            node_pointer n = rtree::create_node<allocators_type, leaf>::apply(allocators);                  // MAY THROW (A)
            subtree_destroyer auto_remover(n, allocators);
            leaf & l = rtree::get<leaf>(*n);

            typedef typename rtree::elements_type<leaf>::type elements_type;
            typedef typename elements_type::value_type element_type;
            elements_type & elements = rtree::elements(l);

            values_count += elements_count;

            elements.reserve(elements_count);                                                               // MAY THROW (A)

            for ( size_t i = 0 ; i < elements_count ; ++i )
            {
                element_type el = serialization_load<element_type>("v", ar);                                     // MAY THROW (C)
                elements.push_back(el);                                                                     // MAY THROW (C)
            }

            auto_remover.release();
            return n;
        }
    }
};

}}}}} // boost::geometry::index::detail::rtree

// TODO - move to index/detail/rtree/private_view.hpp
namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree {

template <typename Rtree>
class const_private_view
{
public:
    typedef typename Rtree::size_type size_type;

    typedef typename Rtree::translator_type translator_type;
    typedef typename Rtree::value_type value_type;
    typedef typename Rtree::options_type options_type;
    typedef typename Rtree::box_type box_type;
    typedef typename Rtree::allocators_type allocators_type;    

    const_private_view(Rtree const& rt) : m_rtree(rt) {}

    typedef typename Rtree::members_holder members_holder;

    members_holder const& members() const { return m_rtree.m_members; }

private:
    const_private_view(const_private_view const&);
    const_private_view & operator=(const_private_view const&);

    Rtree const& m_rtree;
};

template <typename Rtree>
class private_view
{
public:
    typedef typename Rtree::size_type size_type;

    typedef typename Rtree::translator_type translator_type;
    typedef typename Rtree::value_type value_type;
    typedef typename Rtree::options_type options_type;
    typedef typename Rtree::box_type box_type;
    typedef typename Rtree::allocators_type allocators_type;    

    private_view(Rtree & rt) : m_rtree(rt) {}

    typedef typename Rtree::members_holder members_holder;

    members_holder & members() { return m_rtree.m_members; }
    members_holder const& members() const { return m_rtree.m_members; }

private:
    private_view(private_view const&);
    private_view & operator=(private_view const&);

    Rtree & m_rtree;
};

}}}}} // namespace boost::geometry::index::detail::rtree

// TODO - move to index/serialization/rtree.hpp
namespace boost { namespace serialization {

template<class Archive, typename V, typename P, typename I, typename E, typename A>
void save(Archive & ar, boost::geometry::index::rtree<V, P, I, E, A> const& rt, unsigned int version)
{
    namespace detail = boost::geometry::index::detail;

    typedef boost::geometry::index::rtree<V, P, I, E, A> rtree;
    typedef detail::rtree::const_private_view<rtree> view;
    typedef typename view::translator_type translator_type;
    typedef typename view::value_type value_type;
    typedef typename view::options_type options_type;
    typedef typename view::box_type box_type;
    typedef typename view::allocators_type allocators_type;

    view tree(rt);

    detail::serialization_save(tree.members().parameters(), "parameters", ar);

    ar << boost::serialization::make_nvp("values_count", tree.members().values_count);
    ar << boost::serialization::make_nvp("leafs_level", tree.members().leafs_level);

    if ( tree.members().values_count )
    {
        BOOST_GEOMETRY_INDEX_ASSERT(tree.members().root, "root shouldn't be null_ptr");

        detail::rtree::visitors::save<Archive, value_type, options_type, translator_type, box_type, allocators_type> save_v(ar, version);
        detail::rtree::apply_visitor(save_v, *tree.members().root);
    }
}

template<class Archive, typename V, typename P, typename I, typename E, typename A>
void load(Archive & ar, boost::geometry::index::rtree<V, P, I, E, A> & rt, unsigned int version)
{
    namespace detail = boost::geometry::index::detail;

    typedef boost::geometry::index::rtree<V, P, I, E, A> rtree;
    typedef detail::rtree::private_view<rtree> view;
    typedef typename view::size_type size_type;
    typedef typename view::translator_type translator_type;
    typedef typename view::value_type value_type;
    typedef typename view::options_type options_type;
    typedef typename view::box_type box_type;
    typedef typename view::allocators_type allocators_type;
    typedef typename view::members_holder members_holder;

    typedef typename options_type::parameters_type parameters_type;
    typedef typename allocators_type::node_pointer node_pointer;
    typedef detail::rtree::subtree_destroyer<members_holder> subtree_destroyer;

    view tree(rt);

    parameters_type params = detail::serialization_load<parameters_type>("parameters", ar);

    size_type values_count, leafs_level;
    ar >> boost::serialization::make_nvp("values_count", values_count);
    ar >> boost::serialization::make_nvp("leafs_level", leafs_level);

    node_pointer n(0);
    if ( 0 < values_count )
    {
        size_type loaded_values_count = 0;
        n = detail::rtree::load<members_holder>
            ::apply(ar, version, leafs_level, loaded_values_count, params, tree.members().translator(), tree.members().allocators());                                        // MAY THROW

        subtree_destroyer remover(n, tree.members().allocators());
        if ( loaded_values_count != values_count )
            BOOST_THROW_EXCEPTION(std::runtime_error("unexpected number of values")); // TODO change exception type
        remover.release();
    }

    tree.members().parameters() = params;
    tree.members().values_count = values_count;
    tree.members().leafs_level = leafs_level;

    subtree_destroyer remover(tree.members().root, tree.members().allocators());
    tree.members().root = n;
}

template<class Archive, typename V, typename P, typename I, typename E, typename A> inline
void serialize(Archive & ar, boost::geometry::index::rtree<V, P, I, E, A> & rt, unsigned int version)
{
    split_free(ar, rt, version);
}

template<class Archive, typename V, typename P, typename I, typename E, typename A> inline
void serialize(Archive & ar, boost::geometry::index::rtree<V, P, I, E, A> const& rt, unsigned int version)
{
    split_free(ar, rt, version);
}

}} // boost::serialization

#endif // BOOST_GEOMETRY_INDEX_DETAIL_SERIALIZATION_HPP

/* serialization.hpp
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
*/