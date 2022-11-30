// Boost.Geometry Index
//
// R-tree nodes
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP

#include <type_traits>

#include <boost/container/vector.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/varray.hpp>

#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/node/scoped_deallocator.hpp>

//#include <boost/geometry/index/detail/rtree/node/weak_visitor.hpp>
//#include <boost/geometry/index/detail/rtree/node/weak_dynamic.hpp>
//#include <boost/geometry/index/detail/rtree/node/weak_static.hpp>

#include <boost/geometry/index/detail/rtree/node/variant_visitor.hpp>
#include <boost/geometry/index/detail/rtree/node/variant_dynamic.hpp>
#include <boost/geometry/index/detail/rtree/node/variant_static.hpp>

#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/is_bounding_geometry.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// elements box

template <typename Box, typename FwdIter, typename Translator, typename Strategy>
inline Box elements_box(FwdIter first, FwdIter last, Translator const& tr,
                        Strategy const& strategy)
{
    Box result;
    
    // Only here to suppress 'uninitialized local variable used' warning
    // until the suggestion below is not implemented
    geometry::assign_inverse(result);

    //BOOST_GEOMETRY_INDEX_ASSERT(first != last, "non-empty range required");
    // NOTE: this is not elegant temporary solution,
    //       reference to box could be passed as parameter and bool returned
    if ( first == last )
        return result;

    detail::bounds(element_indexable(*first, tr), result, strategy);
    ++first;

    for ( ; first != last ; ++first )
        detail::expand(result, element_indexable(*first, tr), strategy);

    return result;
}

// Enlarge bounds of a leaf node WRT epsilon if needed.
// It's because Points and Segments are compared WRT machine epsilon.
// This ensures that leafs bounds correspond to the stored elements.
// NOTE: this is done only if the Indexable is not a Box
//       in the future don't do it also for NSphere
template <typename Box, typename FwdIter, typename Translator, typename Strategy>
inline Box values_box(FwdIter first, FwdIter last, Translator const& tr,
                      Strategy const& strategy)
{
    typedef typename std::iterator_traits<FwdIter>::value_type element_type;
    BOOST_GEOMETRY_STATIC_ASSERT((is_leaf_element<element_type>::value),
        "This function should be called only for elements of leaf nodes.",
        element_type);

    Box result = elements_box<Box>(first, last, tr, strategy);

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
    if (BOOST_GEOMETRY_CONDITION((
        ! is_bounding_geometry
            <
                typename indexable_type<Translator>::type
            >::value)))
    {
        geometry::detail::expand_by_epsilon(result);
    }
#endif

    return result;
}

// destroys subtree if the element is internal node's element
template <typename MembersHolder>
struct destroy_element
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline static void apply(typename internal_node::elements_type::value_type & element,
                             allocators_type & allocators)
    {
         detail::rtree::visitors::destroy<MembersHolder>::apply(element.second, allocators);

         element.second = 0;
    }

    inline static void apply(typename leaf::elements_type::value_type &,
                             allocators_type &)
    {}
};

// destroys stored subtrees if internal node's elements are passed
template <typename MembersHolder>
struct destroy_elements
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    template <typename Range>
    inline static void apply(Range & elements, allocators_type & allocators)
    {
        apply(boost::begin(elements), boost::end(elements), allocators);
    }

    template <typename It>
    inline static void apply(It first, It last, allocators_type & allocators)
    {
        typedef std::is_same
            <
                value_type, typename std::iterator_traits<It>::value_type
            > is_range_of_values;

        apply_dispatch(first, last, allocators, is_range_of_values());
    }

private:
    template <typename It>
    inline static void apply_dispatch(It first, It last, allocators_type & allocators,
                                      std::false_type /*is_range_of_values*/)
    {
        for ( ; first != last ; ++first )
        {
            detail::rtree::visitors::destroy<MembersHolder>::apply(first->second, allocators);

            first->second = 0;
        }
    }

    template <typename It>
    inline static void apply_dispatch(It /*first*/, It /*last*/, allocators_type & /*allocators*/,
                                      std::true_type /*is_range_of_values*/)
    {}
};

// clears node, deletes all subtrees stored in node
/*
template <typename MembersHolder>
struct clear_node
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline static void apply(node & node, allocators_type & allocators)
    {
        rtree::visitors::is_leaf<MembersHolder> ilv;
        rtree::apply_visitor(ilv, node);
        if ( ilv.result )
        {
            apply(rtree::get<leaf>(node), allocators);
        }
        else
        {
            apply(rtree::get<internal_node>(node), allocators);
        }
    }

    inline static void apply(internal_node & internal_node, allocators_type & allocators)
    {
        destroy_elements<MembersHolder>::apply(rtree::elements(internal_node), allocators);
        rtree::elements(internal_node).clear();
    }

    inline static void apply(leaf & leaf, allocators_type &)
    {
        rtree::elements(leaf).clear();
    }
};
*/

template <typename Container, typename Iterator>
void move_from_back(Container & container, Iterator it)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!container.empty(), "cannot copy from empty container");
    Iterator back_it = container.end();
    --back_it;
    if ( it != back_it )
    {
        *it = boost::move(*back_it);                                                             // MAY THROW (copy)
    }
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP

/* node.hpp
AXtlGad6i5p9AbbeKJtBVM0Dl32XWxcip09bGlWKvwle2Ml+NYDCR0OTNcHm0K6hVpvoBYB1D4Io4shWnTnYzN8Gk6f1sHl0GnpwG0lmSxilczvcWmMJOnUdocyH0dQpcxXK2wXr1kX2PO+11v848NCtF/f9HniF5nkx0C3k58XX1ZYRyDoR+LRxKtuBFuaH5X6ADn4Cgc1bk7uD5ovhh9OwHB5XOy+qDTWzMWnXJkp1O81NlKoxqwz4D2fSQb537bQM7ZiNieZe1cf9HsgRyCV1oYHaYkoUl90AAvMS4i2Qxjjz6uFZpRNlxKrMaZAC1zdzE8239G3oIJI8Xlh07LMh5BLdst8zHR5FaVEnPCpTCEW5WNljSddFLfFWymhX7fiW2NeIozaCbTnzkuZh2fMjztnOK7b7z/pCsbMRj1TtUG1nzcT70tfI7IP/HsY13YBT47yo8Aj4NpAZQ5nCepn5Iv055kf0aFlszjG0U3v7mreZKamHhIFiiDLxWpV3CphOmRkLjJwurm10a0lhIauAmJyWWrXX3vRvNR1udqbqhpwK61eso540YdGAY42s5o/N1l+J/+Sr393QRd0I1WJr2SjYUC3MgF2Du0yTZSlNWYDlnF/A2IV2MuV8mHMBy1KaVjnhcHxy/Yb7GV+ImASIDYuIPGrrxVnbx86RtOkQFM1Z2a+ciM/ddVvq0hDPTG/rPw6RtlkmfbN06T2W+Bbx9e0gvsaLYzTH3V6/2g3e1Fr8aPGloYQ/5sQvRPmOckKPN+x8Wmb8kMBayjS2aA2fYb6HmBq5aEgtBz+ZHawxtkRvGWvYGKYCnT01g60vXH49T916J3PLx89P04mX8WQHTht8R/UC/Qwjv83BLAwZHnZ2EgqSgmApg73IBYL5xv+Mc9MGWskJHem55HYuKRyxLaIlz2Ye08DNYHjteaTt4Vd6z9EMLpjbfswAa8aEoaNXp/d/mdDkJ0tF6YiyOnEr/9Rg5BaRugjE8YwF3YIuZaXNLO+O4i5rL57TXkShRMZA7RBX54+eGcG7KNZlQ23Vhuh1Zm/9k5UdvfE07x2kqzxnttfk2Mr2ndY0C3Ui9b74mZIYkHr4uZM9fWwG7KDlPc+ISKeLS2rILgvurwanY/453r7xFeAzU0Vuf1JrBof+5PdRje6iKdtt46xmdQaZ1FTa0vwpOek/iT2fOJ3bLZok51NzT1WS86vim4pNS2P1RkMZTIMvaQy8Dd792uoVfbaf2WF34ndveCBs+KP7GUzc0KC5aWn9JAqz0zq+4PvIFG3sMtBqchE/Z1f/UZWHY5wy/0xXNgd7G2T07POBt+HkG7wO43TMqXVrhcfJF0cLdafYBXQzPXpXbN85wS3JCTipp3eb2rqukddslq9cwkjepjpk4RehfV72In7PagH5Pe+ZuHF1cMl2c2IGq4F61NnIR9ovUSJ1Xtfobv2deNM0nE3Dnj5c/95uKD82CPUeRL4hsQg2wt6qMOoVUE8H7i66q9JJ0Cvqs2dHs0DVmI41FZjTI2YXxS1Vkjy06G5fcbYXAQQOFygf9VCWRt53jXkshLLPGeI/b84Rzf2S/JkFmQ8MwxmNrPbfUJcIXqMBnY1uq6FXvZfiym5CpdVMMx5HUcCBtidnIgYEc9nZw975e14Xm6G2AsMqZnXHWMnTVKfJL74PIV478R8f5xaeVOZciXpItijGE1YETqUwO3DF9A0CTrGEOqzMXIIWaulak4OmqOaKFI/73LfjVvSSYOuRsPkHZ9Idf8fMyHgEZxYyHxF8IpUTcMZ21ZYzog285rLXLgVdCaL0+HVPsrk/Rd0PtA0RuigsaT0jDfZsb2YIKRDP8CU2668NX+DNPUreixI81m43m+n9ursUdP8YDwQYsE7fpN4STZfCrLFHK/x1ZgR+WJ3/1IclbIyHb0uOXi6msYA83VV/hnbSWE3JK2l/pvwo3lo/O6gSpiE5wvDQ7YnMDULzPgYJAg7hI7sOb2ro1qbwc+nkB+Zt7/dhH1xCbla9UjlZ1GnrE3vl56aD866pdAO5ThE4WQx2YdBh5RaqysWtRbtY8syl3UcLBG56Bgs8WAj5gC+A/jP8oz/E9JC+MojizScuY9XcPPqORH07/k7SdVGMlYldg+37j1LaVq3Oao3qSgf/9cPVwuxvzmcWUqbdUbOIVt09OIPWJ00aNdHFxHFDqnS49VU7yWaurWOyFoL7Ci9KFsoitzdd89bHSuRiMkPI1aM+zorcSerDxTtO/7XFYHcDqmlP/tz2qV1UkCcKgxSRTixLaaaIOIMiU9cdVUvyCKU+hyrKRbkKusaHWtmypGdKTymFBgW3hdWHm1fMFu6Mx3z75aTIec9A4ZD6HHi5W5I2ce7EjSM3YL/sA3ImTVIk2EzkRfFHCWwR5YnNnTIldT1zd2m+85HA3RzkB+2n60fNXVG745ZLReIgNB4alwG8qAWI1mELW5Y0fsoYjgPyXC5Am5e4C4IehgbENZP/RECJqd7VGllr0pUBbX3+X+thdz4W12u4PTJXG9Rm8zUEG1mDAQa3jN2R+3hnqCdVxUVfpyhR8jXoUvc9EeFCMAYZ7qNPGMf4psk2W26ag7jg4aEGMQGyT9nTpKUw1xyDM+YVck6hH0Fb/CIviVdH4+bTtc8L02JrWENyqWRBBWpFsnxYZ1nZoq4vHfuavNeVvBpwlwGB3l/qHNqszMnd4zP798jThlVqkol+ygJV1jqjycbMNayrQ9hQP7pgWR6h76kZGt0ktT2XeKhjQqSqIWnsfTR37XjyLq6WhDIqTKLiFzSrIdk7ZA6e15hlaOpXHVUhOF3YFdsYNb8yjvOGiuOlO81/5++eXN2vnCjktojgtCG5A7X+RZBP9PPBN7SM6E8Clm57//WfpZZOQRujp8seJzIRpzbPETZxjZjQbon85N+pA7FvUBP/O6Eu1VnANZgBKzRxRuW4e3P3Te495PMgVRDSRko+4vTg70mYn4I29cNYDj1qftL1mMovUHOxNp4NK5hrNsDcyCuymOwq2/w2hX69InGXo2yTZcyAiXiP66jCzpxx3EC54nl223BBZYfwcOpBx1YX/cTcVsiBFp5FkXRW4U2q0ZrOjl0PK06oVNXvU8L3d9TPjJy9/Rbvpxqk1UPtRiuw7Lj9EsA0gu+ir15b2gTnVcFPm9qT3NJUhWL/gqCCokG+Lu3hR2o4v9RLma2xjW2sXbXI1p0GndThvb49S6s/+GSlI/EVCt0JSERLVDlUbJc4htvhvXGV69BQMWBBxsZdoAIy4zjqfvjbxgl7XPTv5m3qk6Q/Y39k7gDRhJmNs79QDp1CxgCW+SW9XoKDMWGSZFSCsbKBBXYyK001r/CMADMRxQh4DfY5GcW5gkspa2Gah4xhviE2ai7oZ/ohktUw2J3aOn2x2JblJbRSWa9N+s9NyEukbQHdWSd+9zx+UObciYVbTE307sW9sBONhwCkOlIVnSoTZiiKqc8cAZ8Gw+slAleO0vQbVgxqYOkuyxv4oo12vzBIPXxRCkh5cyc3lKSRfKsNgGRnUx/l3LiZX8TDZPcuswtYl1NHSm7FbLax5MZIl/YvFy1YCdQOkZcoyOvXTxS7qWQjDPhRlAeStwZoUAO6M+KM5b8uzz5OM5ALv+MFOGbU1SKaNmL2UP6Nfoy1/uvxd/utr2kUMjIyb+TcmZV7dcJ282BoT01v4YZzcFx3svIN4L9vKERMAlcK9QxCgd3h214zf6DsZu3kmXD2Om/65edYjNBl4qr0sEgR+f9S8HckPLkTGj5B7LweFQ9b+KwHyhaV0psOr+mXXMo8S8j/g3LVgyWbGKu854t7YYzkNSwKI1IaxxXv5zrkSIeSZhz/GvxCOyddEmaB+1Kapbquht0xS1pm2VXmci7K3bA7e3lQ+wD7DAM5G3jJsYjWBugURnEBSHWm0o9/8pwoJOycH1DrtNW4N4Aukp76IwqmTgk9Y1vMMvvs+6sntq6UXAUnj6iLwipl4XhDd47YRETtn//jgEOR3hRvFnW5Cy0QZX1FuFgI/vhEwipRAD3smiS3dSVIrkJ2huyO9QjDuo7DjU0Ps0ttstrwumLd634Kd9f20Jt2ganTpXI+JqHLde2vEnqS9qFvO1uY2bXyS8Or59N57VlljsBMjp4YkTlAwGbnEW2nwQiAbRPHTVhQleL8Q+0EBdEFTOTK0BnBs6Fr1dv6QIQl49bC6UfAxntwJWLIfoXyJnzstNLugnzn+6RoJRU7B+c89Ha6Ew/auxd/t0Ruucy2kq42OWpKDe8nE7UoVyZvmZGc8crVGXeb6W8RG8ADGWZaELgK/AwglAremRz3QHnCoX/p7eja2cRD6YY9sn28mRXlO4hiQHuID/97Y54ZJ2CMB+EYOPz3YkxWQGF8LVtgRmsARQAuq3Sa7zZQ9JN59QL2h1qTf8dzLH53kebaoLVKbWWiNvV8Cr2ZZQ+z0XmP18XGma00fQyg2RG7rC+TtzBAC1V8DZShJMt2EjT4qusbsnOorB2kmqPYuujzpA1itYx3FvmaOh9q1rzESIr1ESUVYkJLGlsdu9yrarSO1NgRcOQoeicer0ub6ESfMaVsgIOQzkto5o62aWPU5AJNlBIYU8B0yvjOl7KKa4WnnP4ZVnU2+LDpiD5pbsBNv5/ZOdUrwWCVi5K17xTxnYenYdP5Hx1tTHgSZSfjohwK2LTmYuQs0qNgNvoBhkERnBV3u4CMyTIjVOIGcSkLJKX7UkaEQxfM9vc/B2m0a7ETWcbpN7oukNyhmYFU0LzR54ibgqpPYqg2vw6IPhinRQ8XJZ5+PcnT6FvZf3rr/o2jBso3YJ2hESVwPNzlDtgaP2FnCWPGMG+ymARAsA0jmhfVVIB7OgUiBGYEGSGm/BOaCgsOTRDsjQDXEp8z+6hB7w5/yxbsc+8ojrzqBcAfi2xJWanbZU4yKjlCy/CfcLsCmCzD2i4qPUAFrZAftPzEEuykrEHdI6EdEYCUpesiq+aw9YWMYDDkBFNZBs9TxJ5Q2c4oxeFvdkJflfEyExjRIC8T0Zh7whilAUu9qoGprSZdVYwz/pbAzew+/heFNeurJd+GBV4T3TreVXHexc4rg234+G5UV0VARY1oxW5Ld/ApeoEUgRHr38CYuYknXx+ZHxgVaZBeSTxLFxeiyDczgAqQx7HYC3SA2VDBW5n/IQP6gX2Mb/HdWtxtUKawK+lGnVQe48q62NWoK6IYl0vWNnpsSxeTN7F/Gj6aIFS6Fuj2Gpwne3/2WQ3oHYgXjhHRwmg/ksp84RNqt1jv/N0XYc+fTjXoF83m51HhXIJ1Dk9YmUE2Scw3/mGpyWRTiPl/ziExnwIpiS6H9B6SEUS9OA26WjJr4C1BxV83xwuZrhDkLnWSdOqh6f9K99p38T2C6DLC+OI5dCNj70Ol90TbW7QWaYJ7ug6WYdONiMEdAiUPUZ4p/fflCHpByNqh56ye9N6xlGkzdzbwYsy0sapcMdO+e50OmDA8okNFaZl6NZCLusCzPoejRCJCrKg7EzDk72x2j6SKgEVdIVapAXj94aXh5p5x87qe2SWmWqs3LUAoemfWTrpcQq9suMAQjdmnYIjtFFoDKqhtVFtatrQsKjRKG4sIT7oi7qzHbSCrLjmpalxpJz3oS7tV0adM9wUnbsF3aDnXyfEA62gPWilfssKxv85DsLMC0lT1ycOWtl+mMi0pGlrVB8tYZfx3de9qczyPzDpTKQY5duu4jPZMpYkLSEmOi+3H3G6E7hC6qEkNmOHucHx/bKL/E6pBCf2binRI6yE9Yp+IT4DiyrFY21aBvD3eNeyFbP8c8GiQ8zlsbfAMddPabcPLWEjfugAgcMSQU8Vo/sFapaFp7Iul6re2u/oruzuQ/TsL4p/AxSlS5kR7dSHhDZUGwLgSaW3v6w3wPJn0g/eG2mVHACwAqfVb4q0NG+M8V9uufG1n9Av9bO2vukB2tW7zXrvD0DekvOVKHxw++6n3WG+JX4XfMD8CtzDOPu/2tfbcRkEMW+p/zruND2HsSDAtphlS060mkUwtb7eEHYM/ZRo0RahnMP/BRkxxq6bomMLlHyldDT+H3NoIUpqPgpxAALzIEzyoFVSY/x64IB8MQ9cj1DymuuO3jO8Kx0DvsRUc2+I5y9OSS7resNmVtYJpHwR0dRTkBmZTjT564SzMXK88c334fPp/T/5MU4jj1fBAydp2/+cTa0XKGsiShTUFZT9GvPdRv/t4+GYMzCFhq9/1QxKv6loZpTJqaVLdTKve2i+okNfI6Iy4FQZZ3Ue5McUAF3tl5ypZyu3pG7wAddATHItWSb/hNyEGSCvv11dTQaytcNvMLN04sEAV7a3lyuXVNkrvK/sTDTWNiWchS8/yrSkEPwWvvEH1Hn1s1L1KSRpfBxsIUmVfKmVzkua07XHYZc/LbuFOt40jiyRlmmhzhNO+vhUY435Tsugk2JDxtoNxMtfLkx4/Qm7tLspRWH+XyYAMy7WYZb3NFJmg+DqlFp9gOcfqzF0d2NQBC3GU9DWQc5V0lDngU50+5BgvJJsQyYDmdij1hhGBsBlo3gk8F/kW/6xVriH/Hngu97nPrmtRG5DK3LXTAItsFJXyevVQePPsm8hrfH8v/oETr1YyCIaltVXFgX4yuGx0EXo079lEkVOMdL8OWTdsk5FUbLCmoUvvxQXvxVgaZsR1cSTgocCb7LApbQvilvPx36QWlq2T6tEtZYgbVXfgxfLi1JOsj7bZM9R74Ff4nlsn9F5nCbooJJF6ZBm/r4DgWSDZmoE2g2GayRTBMRUT7hic4E2ApK/IvDpINcOyNBUvjcDGnMAj1NSwNiuExTVw4TPzx3/3RgSP+8RmvMcktHbjnfdOe+WPKkN/6gWI49NN8DhAVT4JtNEacd5zpTQskRmvpZ5gMNjcwTwBUrEIUA1bPF+aqQHAVdCuGmKm4N31YQoz6sabTA0Z0ZMexzRlQjwNGZ8SOXGyqn4XnOY8IDYwir0SP8Xl6nasoTbGZ/zVLldPu6rni/ye7ifC95feqLGBxLqw48xCPckItoqtNPc2AsQZhoANm7hTWS+HJ+1sCDn7r147R4yBRslxTJwo/5GcfwZTQMfETAzlgb0vIb4lIrNbTxpeKeOuuxyFlzSnUbXPzDlyxIKE4KraWS6NVDHIdeo8c3rx8ctgZHDoGIKykccHnseuiYk6rkGNiZn72WHOB55jXc66jDp6cgswXx5zH/CRpuA7WiPMDZgi8jPNsws7UcSmoo0ZaytZltcBrp7L3uySiJqU3kptf5A9/Hn57/lGaugXaI3omt1WyS7vZXnqDqndm8MnXxCVk+VVExL3gjDyWaL3AqdU/FhwYZnQPJ0EdIS2acLqJUo3TnE7dOtqeixDbrdhdl6NP4F0p8Dp2iUNtc5oRt+XLMM8NPRd/qRrG9lpcHT6b/XnBDw24Z3xsWeOgHFduUXcA82e4hD2aNO2to+hKAUukamA6y7/LWctts2DM+gq+HT0dTEe/5h7YWaehq+Ro7JcZGHFfFOAowizUOGPuTR+EiKj+UPgkmd0ak2/AXQ7jvOOaJ0RZmL81ndmok6zHOAS2pJluqJhzRWpM1tj5NYItla5Z4N2hefKSYbW
*/