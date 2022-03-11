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