// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_SERIALIZATION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_SERIALIZATION_HPP

//#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
//#include <boost/serialization/nvp.hpp>

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
namespace boost { namespace geometry { namespace index { namespace detail {

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

        if ( elements_count < parameters.get_min_elements() || parameters.get_max_elements() < elements_count )
            BOOST_THROW_EXCEPTION(std::runtime_error("rtree loading error"));

        if ( current_level < leafs_level )
        {
            node_pointer n = rtree::create_node<Allocators, internal_node>::apply(allocators);              // MAY THROW (A)
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

            node_pointer n = rtree::create_node<Allocators, leaf>::apply(allocators);                       // MAY THROW (A)
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

    typedef typename options_type::parameters_type parameters_type;
    typedef typename allocators_type::node_pointer node_pointer;
    typedef detail::rtree::subtree_destroyer<value_type, options_type, translator_type, box_type, allocators_type> subtree_destroyer;

    view tree(rt);

    parameters_type params = detail::serialization_load<parameters_type>("parameters", ar);

    size_type values_count, leafs_level;
    ar >> boost::serialization::make_nvp("values_count", values_count);
    ar >> boost::serialization::make_nvp("leafs_level", leafs_level);

    node_pointer n(0);
    if ( 0 < values_count )
    {
        size_type loaded_values_count = 0;
        n = detail::rtree::load<value_type, options_type, translator_type, box_type, allocators_type>
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