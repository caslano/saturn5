/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_ITERATOR_07202005_0835)
#define FUSION_REVERSE_VIEW_ITERATOR_07202005_0835

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/deref_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/next_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/prior_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/advance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/distance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/key_of_impl.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename First>
    struct reverse_view_iterator
        : iterator_base<reverse_view_iterator<First> >
    {
        typedef convert_iterator<First> converter;
        typedef typename converter::type first_type;
        typedef reverse_view_iterator_tag fusion_tag;
        typedef typename traits::category_of<first_type>::type category;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , category>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view_iterator(First const& in_first)
            : first(converter::call(in_first)) {}

        first_type first;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view_iterator& operator= (reverse_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename First>
    struct iterator_traits< ::boost::fusion::reverse_view_iterator<First> >
    { };
}
#endif

#endif


/* reverse_view_iterator.hpp
I230nJeX6P6hlFwrz6GfPHujudHyMaOzN5oPzayVZu85fTyVWdYAFTTSMi0vsExYsJwB9CDtzquDr4QZyhugKjM6l6M50RKZzTuhyUZlohVjRudyNFsFA9iYncl+sSWVicbbIv/OFHNHy8aMzuVoXrRqLPdV6/osorjKBugA0m7XqbOB8qtigLHM6FyO5kO7xixpzuwbwvx2A5iksXM55o5WntnoRb1KCrPHGcAqjZ3LMXe0icxe7jo9SJi1qgHmMctfZtRUYQG0rMzo7I0G1Qwwg9m0xxWU56bdwYd2ULE/ca10yXSwGll1XCvMhq/v+0CYrQaOETP6O2E0B1oUMzp7ozlD4+QZGs0davI8j+ZNUWbEGCuZP0Vcn6jHVYUFQ03OazRDzRBj52vML9TYHMT8Qo2d5zG/UGP3D5hfqLH7DswPbRezFrcD8cI8tQwQzSzLrIT8lDvaTGbN7hcmc9cOjaNzOZov1Ng9AvYZWg5m6fOUnibM+mNoXMsMlz9Rv6SwG+mm0Di4Qo2d2TH3FLa/VvvewgKhxu4RcPzqhBrdk6DZQ43dy3QEJ1r+sG/2AorA3RKVdMIS6ytzXrG/fZlaC/OjmSOkef6cHRBmayzrQ2PPdLBMtO+Z0TMdNA9aJDO6TqN50e6zdv7aSvuI3iXbwkDvq/wL+vY9NMSZSVhiSwNMZ/Y2qXkhYdZWBqjIrFCRp2eEOdH8zFzFiw8T5mptgG3MWnVPuk9xbQywXistOcfijcL87QyQWSNNvzrXbWG2Dng9YuY5+/6tMF9HLBOkzbtbUb7rI8kAfRV7CQDZA2FDhdk6GcDDTNN/Vnph0NkAvZgt+P2/qsLcaLOZ1fves12Y42e5l78CAG2PXr2pLWg1mR3Rtz5F75joIq/9QejVPmZ50ELvTUNzKPYWevYN+btBtD8Uewd9e/atl/mOsGBXAzTVSMtUcm4OYZ7uBrAwWzTKdFIY9FT2ecVWLHgkrZcBSjMr+qhdkjAH2mZW5rGP65sKc/ZWclBsb93j04QF0Pozu337zB/CXH0MYNBKK5W1jFeYtZ8BzoG09Jqui4TZ+uO1nxld+9EcaLNYO9fV8bUmG2iAKSDthGFcJcp9kAEiWFze7Ll6UdxgAxwCaW/yn99INsQAeZjx95i50LIw4+8r8QyRZ74PADBt2ND1wvzDcH9hdvWO5S7N6xEGaMTMeqVhM2EBF96vMNulXVxKmGuUATqHSXs6JhvNXd9Y3Hu00j5+2C3fUzoBDchC3/eLFs+M/z2XH+0nZh1yWnpQDhMNMJjZ1jO1HBSHlkda6LuuJqVuNrRCzPj7X5xoscz4e2q8aM2YlbTvOSXMOtkAoyKkBfVvXggz/GqAsuHSOq/53FKs98S5Bvoe0j+43ov0/lhWWAAtXiMtT80xGmHu+QZYCdJeQe5OVOYCA7RmlnQ5eJXKRItlNub6PL8w60IDVGaW1XOwsTAnWktmPSZUPSYsiDafWc7NM2OFeRcZoASzfNkntaU4tL3MRkQ53lM7FxugfYS0qn/XpDjPCrxvDJMWfDKlB9W3xgDjLdI+X5tObUk8bIDHrMxBl3IFhPlOGaAeSKvty/qO+uW0AfbopN30jt8lzHHbAMeipC0o87i4MP9LA7QBaZ2zVyxDca/wGpBGWuV0eSkH2we8BmilFcrSq4gwwycDbABpjVvsbUH9iXab2Y3MS2pS3GcDbNRIa5I9H5ntP7w+gLQS9Ut8oL5GS2LW8EH2H6lfvuIYMes7fqyN4tBqMmv6uvxTYQBGeMbyy3Om1TkavzAjDAJplc7toXY6wo2wiFlC9OD81JYIIxTic35jnUs07mixYdIy9Np7iyydEUqBNPk=
*/