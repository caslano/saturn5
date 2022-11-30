// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden.
// Copyright 2008 Hartmut Kaiser.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_QUERYING_HPP
#define BOOST_PHOENIX_ALGORITHM_QUERYING_HPP

#include <algorithm>

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_find.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_lower_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_upper_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_equal_range.hpp>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>
#include <boost/phoenix/stl/algorithm/detail/decay_array.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>

namespace boost { namespace phoenix {
    namespace impl
    {
        struct find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::true_) const
            {
                return r.find(x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::false_) const
            {
                return std::find(detail::begin_(r), detail::end_(r), x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& x) const
            {
                return execute(r, x, has_find<R>());
            }
        };

        struct find_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::find_if(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct find_end
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct find_first_of
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct adjacent_find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r));
            }

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct count
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_difference<R>
            {};

            template<class R, class T>
            typename range_difference<R>::type
            operator()(R& r, T const& x) const
            {
                return std::count(detail::begin_(r), detail::end_(r), x);
            }
        };

        struct count_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_difference<R>
            {};

            template<class R, class P>
            typename range_difference<R>::type
            operator()(R& r, P p) const
            {
                return std::count_if(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct distance
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_difference<R>
            {};

            template<class R>
            typename range_difference<R>::type
            operator()(R& r) const
            {
                return std::distance(detail::begin_(r), detail::end_(r));
            }
        };

        struct equal
        {
            typedef bool result_type;

            template<class R, class I>
            bool operator()(R& r, I i) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            bool operator()(R& r, I i, P p) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i, p);
            }
        };

        struct search
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, typename R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template <typename This, class R, typename R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct lower_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.lower_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_lower_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct upper_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.upper_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_upper_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename T, typename C = void>
            struct equal_range
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename range_iterator<R>::type
                > type;
            };
        }

        struct equal_range 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : result_of::equal_range<R,T>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : result_of::equal_range<R,T, C>
            {};

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.equal_range(val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_equal_range<R>());
            }

            template<class R, class T, class C>
            typename result_of::equal_range<R, T, C>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename I, typename P = void>
            struct mismatch
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename detail::decay_array<I>::type
                > type;
            };
        }

        struct mismatch
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class I>
            struct result<This(R&, I)>
                : result_of::mismatch<R, I>
            {};

            template<typename This, class R, class I, class P>
            struct result<This(R&, I, P)>
                : result_of::mismatch<R, I, P>
            {};

            template<class R, class I>
            typename result_of::mismatch<R, I>::type
            operator()(R& r, I i) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            typename result_of::mismatch<R, I, P>::type
            operator()(R& r, I i, P p) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i, p);
            }
        };

        struct binary_search 
        {
            typedef bool result_type;

            template<class R, class T>
            bool operator()(R& r, T const& val) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T, class C>
            bool operator()(R& r, T const& val, C c) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct includes 
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }

            template<class R1, class R2, class C>
            bool operator()(R1& r1, R2& r2, C c) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , c
                    );
            }
        };

        struct min_element
        {
            template <typename Sig>
            struct result;
            
            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct max_element
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct lexicographical_compare
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }
        
            template<class R1, class R2, class P>
            bool operator()(R1& r1, R2& r2, P p) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , p
                    );
            }
        };

    }

    BOOST_PHOENIX_ADAPT_CALLABLE(find, impl::find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_if, impl::find_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count, impl::count, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count_if, impl::count_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(distance, impl::distance, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 3)

}}

#endif

/* querying.hpp
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
*/