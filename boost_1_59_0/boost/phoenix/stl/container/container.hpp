/*=============================================================================
    Copyright (c) 2004 Angus Leeming
    Copyright (c) 2004 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STL_CONTAINER_CONTAINER_HPP
#define BOOST_PHOENIX_STL_CONTAINER_CONTAINER_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/void.hpp>
#include <boost/phoenix/stl/container/detail/container.hpp>
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace phoenix
{
///////////////////////////////////////////////////////////////////////////////
//
//  STL container member functions
//
//      Lazy functions for STL container member functions
//
//      These functions provide a mechanism for the lazy evaluation of the
//      public member functions of the STL containers. For an overview of
//      what is meant by 'lazy evaluation', see the comments in operators.hpp
//      and functions.hpp.
//
//      Lazy functions are provided for all of the member functions of the
//      following containers:
//
//      deque - list - map - multimap - vector - set - multiset.
//
//      Indeed, should *your* class have member functions with the same names
//      and signatures as those listed below, then it will automatically be
//      supported. To summarize, lazy functions are provided for member
//      functions:
//
//          assign - at - back - begin - capacity - clear - empty - end -
//          erase - front - get_allocator - insert - key_comp - max_size -
//          pop_back - pop_front - push_back - push_front - rbegin - rend -
//          reserve - resize . size - splice - value_comp.
//
//      The lazy functions' names are the same as the corresponding member
//      function. Sample usage:
//
//      "Normal" version                 "Lazy" version
//      ----------------                 --------------
//      my_vector.at(5)                  phoenix::at(arg1, 5)
//      my_list.size()                   phoenix::size(arg1)
//      my_vector1.swap(my_vector2)      phoenix::swap(arg1, arg2)
//
//      Notice that member functions with names that clash with a
//      function in stl algorithms are absent. This will be provided
//      in Phoenix's algorithm module.
//
//      No support is provided here for lazy versions of operator+=,
//      operator[] etc. Such operators are not specific to STL containers and
//      lazy versions can therefore be found in operators.hpp.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Lazy member function implementaions.
//
//      The structs below provide the guts of the implementation. Thereafter,
//      the corresponding lazy function itself is simply:
//
//          function<stl::assign> const assign = stl::assign();
//
//      The structs provide a nested "result" class template whose
//      "type" typedef enables the lazy function to ascertain the type
//      to be returned when it is invoked.
//
//      They also provide operator() member functions with signatures
//      corresponding to those of the underlying member function of
//      the STL container.
//
///////////////////////////////////////////////////////////////////////////////
    namespace stl
    {
        struct assign
        {
            template <typename Sig>
            struct result;

            template <
                typename This
              , typename C
              , typename Arg1
            >
            struct result<This(C&, Arg1&)>
            {
                typedef typename add_reference<C>::type type;
            };

            template <
                typename This
              , typename C
              , typename Arg1
              , typename Arg2
            >
            struct result<This(C&, Arg1, Arg2)>
            {
                typedef typename add_reference<C>::type type;
            };

            template <
                typename This
              , typename C
              , typename Arg1
              , typename Arg2
              , typename Arg3
            >
            struct result<This(C&, Arg1, Arg2, Arg3)>
            {
                typedef typename add_reference<C>::type type;
            };

            template <typename C, typename Arg1>
            C& operator()(C& c, Arg1 const & arg1) const
            {
                c.assign(arg1);
                return c;
            }

            template <typename C, typename Arg1, typename Arg2>
            C& operator()(C& c, Arg1 arg1, Arg2 arg2) const
            {
                c.assign(arg1, arg2);
                return c;
            }

            template <typename C, typename Arg1, typename Arg2, typename Arg3>
            C& operator()(
                C& c
              , Arg1 arg1
              , Arg2 arg2
              , Arg3 const & arg3
            ) const
            {
                return c.assign(arg1, arg2, arg3);
            }
        };

        struct at_impl
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C, typename Index>
            struct result<This(C&, Index)>
            {
                //typedef typename const_qualified_reference_of<C>::type type;
                typedef typename C::value_type & type;
            };

            template <typename C, typename Index>
            typename result<at_impl(C&, Index const&)>::type
            operator()(C& c, Index const &i) const
            {
                return c.at(i);
            }

            template <typename This, typename C, typename Index>
            struct result<This(C const&, Index)>
            {
                typedef typename C::value_type const & type;
            };

            template <typename C, typename Index>
            typename result<at_impl(C const&, Index const&)>::type
            operator()(C const& c, Index const &i) const
            {
                return c.at(i);
            }
        };

        struct back
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef
                    typename const_qualified_reference_of<C>::type
                type;
            };

            template <typename C>
            typename result<back(C&)>::type
            operator()(C& c) const
            {
                return c.back();
            }
        };

        struct begin
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename const_qualified_iterator_of<C>::type type;
            };

            template <typename C>
            typename result<begin(C&)>::type
            operator()(C& c) const
            {
                return c.begin();
            }
        };

        struct capacity
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename size_type_of<C>::type type;
            };

            template <typename C>
            typename result<capacity(C&)>::type
            operator()(C const& c) const
            {
                return c.capacity();
            }
        };

        struct clear
        {
            typedef void result_type;

            template <typename C>
            void operator()(C& c) const
            {
                return c.clear();
            }
        };

        struct empty
        {
            typedef bool result_type;

            template <typename C>
            bool operator()(C const& c) const
            {
                return c.empty();
            }
        };

        struct end
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename const_qualified_iterator_of<C>::type type;
            };

            template <typename C>
            typename result<end(C&)>::type
            operator()(C& c) const
            {
                return c.end();
            }
        };

        namespace result_of
        {
            template <typename C, typename Arg1, typename Arg2 = mpl::void_>
            struct erase
            {
                // MSVC and libc++ always returns iterator even in C++03 mode.
                typedef
                    boost::mpl::eval_if<
                        is_key_type_of<C, Arg1>
                      , size_type_of<C>
#if defined(BOOST_MSVC) /*&& (BOOST_MSVC <= 1500)*/ \
 && (defined(BOOST_LIBSTDCXX11) && 40500 <= BOOST_LIBSTDCXX_VERSION) \
 && defined(_LIBCPP_VERSION)
                      , iterator_of<C>
#else
                      , boost::mpl::identity<void>
#endif
                    >
                assoc_erase_result;

                typedef typename
                    boost::mpl::eval_if_c<
                        has_key_type<C>::value
                      , assoc_erase_result
                      , iterator_of<C>
                    >::type
                type;
            };
        }

        struct erase
        {
            //  This mouthful can differentiate between the generic erase
            //  functions (Container == std::deque, std::list, std::vector) and
            //  that specific to Associative Containers.
            //
            //  where C is a std::deque, std::list, std::vector:
            //
            //      1) iterator C::erase(iterator where);
            //      2) iterator C::erase(iterator first, iterator last);
            //
            //  where C is a std::map, std::multimap, std::set, or std::multiset:
            //
            //      3) size_type M::erase(const Key& keyval);
            //      4-a) void M::erase(iterator where);
            //      4-b) iterator M::erase(iterator where);
            //      5-a) void M::erase(iterator first, iterator last);
            //      5-b) iterator M::erase(iterator first, iterator last);

            template <typename Sig>
            struct result;

            template <typename This, typename C, typename Arg1>
            struct result<This(C&, Arg1)>
                : result_of::erase<C, Arg1>
            {};

            template <typename This, typename C, typename Arg1, typename Arg2>
            struct result<This(C&, Arg1, Arg2)>
                : result_of::erase<C, Arg1, Arg2>
            {};

            template <typename C, typename Arg1>
            typename result_of::erase<C, Arg1>::type
            operator()(C& c, Arg1 arg1) const
            {
                typedef typename result_of::erase<C, Arg1>::type result_type;
                return static_cast<result_type>(c.erase(arg1));
            }

            template <typename C, typename Arg1, typename Arg2>
            typename result_of::erase<C, Arg1, Arg2>::type
            operator()(C& c, Arg1 arg1, Arg2 arg2) const
            {
                typedef typename result_of::erase<C, Arg1, Arg2>::type result_type;
                return static_cast<result_type>(c.erase(arg1, arg2));
            }
        };

        struct front
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename const_qualified_reference_of<C>::type type;
            };

            template <typename C>
            typename result<front(C&)>::type
            operator()(C& c) const
            {
                return c.front();
            }
        };

        struct get_allocator
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename allocator_type_of<C>::type type;
            };

            template <typename C>
            typename result<get_allocator(C const&)>::type
            operator()(C& c) const
            {
                return c.get_allocator();
            }
        };

        namespace result_of
        {
            template <
                typename C
              , typename Arg1
              , typename Arg2 = mpl::void_
              , typename Arg3 = mpl::void_
            >
            class insert
            {
                struct pair_iterator_bool
                {
                    typedef typename std::pair<typename C::iterator, bool> type;
                };

                typedef
                    boost::mpl::eval_if<
                        map_insert_returns_pair<typename remove_const<C>::type>
                      , pair_iterator_bool
                      , iterator_of<C>
                    >
                choice_1;

                typedef
                    boost::mpl::eval_if_c<
                        boost::mpl::and_<
                            boost::is_same<Arg3, mpl::void_>
                          , boost::mpl::not_<boost::is_same<Arg1, Arg2> >
                        >::value
                      , iterator_of<C>
                      , boost::mpl::identity<void>
                    >
                choice_2;

            public:

                typedef typename
                    boost::mpl::eval_if_c<
                        boost::is_same<Arg2, mpl::void_>::value
                      , choice_1
                      , choice_2
                    >::type
                type;
            };
        }

        struct insert
        {
            //  This mouthful can differentiate between the generic insert
            //  functions (Container == deque, list, vector) and those
            //  specific to the two map-types, std::map and std::multimap.
            //
            //  where C is a std::deque, std::list, std::vector:
            //
            //      1) iterator C::insert(iterator where, value_type value);
            //      2) void C::insert(
            //          iterator where, size_type count, value_type value);
            //      3) template <typename Iter>
            //         void C::insert(iterator where, Iter first, Iter last);
            //
            //  where M is a std::map and MM is a std::multimap:
            //
            //      4) pair<iterator, bool> M::insert(value_type const&);
            //      5) iterator MM::insert(value_type const&);
            //
            //  where M is a std::map or std::multimap:
            //
            //      6) template <typename Iter>
            //         void M::insert(Iter first, Iter last);

            template <typename Sig>
            struct result;

            template <
                typename This
              , typename C
              , typename Arg1
            >
            struct result<This(C &, Arg1)>
                : result_of::insert<C, Arg1>
            {};

            template <
                typename This
              , typename C
              , typename Arg1
              , typename Arg2
            >
            struct result<This(C &, Arg1, Arg2)>
                : result_of::insert<C, Arg1, Arg2>
            {};

            template <
                typename This
              , typename C
              , typename Arg1
              , typename Arg2
              , typename Arg3
            >
            struct result<This(C &, Arg1, Arg2, Arg3)>
                : result_of::insert<C, Arg1, Arg2, Arg3>
            {};

            template <typename C, typename Arg1>
            typename result<insert(C&, Arg1)>::type
            operator()(C& c, Arg1 arg1) const
            {
                return c.insert(arg1);
            }

            template <typename C, typename Arg1, typename Arg2>
            typename result<insert(C&, Arg1, Arg2)>::type
            operator()(C& c, Arg1 arg1, Arg2 arg2) const
            {
                typedef typename result<insert(C&, Arg1, Arg2)>::type result_type;
                return static_cast<result_type>(c.insert(arg1, arg2));
            }

            template <typename C, typename Arg1, typename Arg2, typename Arg3>
            typename result<insert(C&, Arg1, Arg2, Arg3)>::type
            operator()(C& c, Arg1 arg1, Arg2 arg2, Arg3 arg3) const
            {
                typedef typename result<insert(C&, Arg1, Arg2, Arg3)>::type result_type;
                return static_cast<result_type>(c.insert(arg1, arg2, arg3));
            }
        };

        namespace result_of
        {
            template <typename C>
            struct key_comp
            {
                typedef typename key_compare_of<C>::type type;
            };
        }

        struct key_comp
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
                : result_of::key_comp<C>
            {};

            template <typename C>
            typename result_of::key_comp<C>::type
            operator()(C& c) const
            {
                return c.key_comp();
            }
        };

        struct max_size
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename size_type_of<C>::type type;
            };

            template <typename C>
            typename result<max_size(C const&)>::type
            operator()(C& c) const
            {
                return c.max_size();
            }
        };

        struct pop_back
        {
            typedef void result_type;

            template <typename C>
            void operator()(C& c) const
            {
                return c.pop_back();
            }
        };

        struct pop_front
        {
            typedef void result_type;

            template <typename C>
            void operator()(C& c) const
            {
                return c.pop_front();
            }
        };

        struct push_back
        {
            typedef void result_type;

            template <typename C, typename Arg>
            void operator()(C& c, Arg const& data) const
            {
                return c.push_back(data);
            }
        };

        struct push_front
        {
            typedef void result_type;

            template <typename C, typename Arg>
            void operator()(C& c, Arg const& data) const
            {
                return c.push_front(data);
            }
        };

        struct rbegin
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename
                    const_qualified_reverse_iterator_of<C>::type
                type;
            };

            template <typename C>
            typename result<rbegin(C&)>::type
            operator()(C& c) const
            {
                return c.rbegin();
            }
        };

        struct rend
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename
                    const_qualified_reverse_iterator_of<C>::type
                type;
            };

            template <typename C>
            typename result<rend(C&)>::type
            operator()(C& c) const
            {
                return c.rend();
            }
        };

        struct reserve
        {
            typedef void result_type;

            template <typename C, typename Arg>
            void operator()(C& c, Arg const& count) const
            {
                c.reserve(count);
            }
        };

        struct resize
        {
            typedef void result_type;

            template <typename C, typename Arg1>
            void operator()(C& c, Arg1 const& arg1) const
            {
                c.resize(arg1);
            }

            template <typename C, typename Arg1, typename Arg2>
            void operator()(C& c, Arg1 const& arg1, Arg2 const& arg2) const
            {
                c.resize(arg1, arg2);
            }
        };

        struct size
        {
            template <typename Sig>
            struct result;

            template <typename This, typename C>
            struct result<This(C&)>
            {
                typedef typename size_type_of<C>::type type;
            };

            template <typename C>
            typename result<size(C&)>::type
            operator()(C& c) const
            {
                return c.size();
            }
        };

    struct splice
    {
        typedef void result_type;

        template <typename C, typename Arg1, typename Arg2>
        void operator()(C& c, Arg1 arg1, Arg2 &arg2) const
        {
            c.splice(arg1, arg2);
        }

        template <
            typename C
          , typename Arg1
          , typename Arg2
          , typename Arg3
        >
        void operator()(
            C& c
          , Arg1 arg1
          , Arg2 & arg2
          , Arg3 arg3
        ) const
        {
            c.splice(arg1, arg2, arg3);
        }

        template <
            typename C
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
        >
        void operator()(
            C c
          , Arg1 arg1
          , Arg2 & arg2
          , Arg3 arg3
          , Arg4 arg4
        ) const
        {
            c.splice(arg1, arg2, arg3, arg4);
        }
    };


    namespace result_of
    {
        template <typename C>
        struct value_comp
        {
            typedef typename value_compare_of<C>::type type;
        };
    }

    struct value_comp
    {
        template <typename Sig>
        struct result;

        template <typename This, typename C>
        struct result<This(C&)>
            : result_of::value_comp<C>
        {};

        template <typename C>
        typename result_of::value_comp<C>::type
        operator()(C& c) const
        {
            return c.value_comp();
        }
    };

} // namespace stl

    ///////////////////////////////////////////////////////////////////////////////
    //
    //  The lazy functions themselves.
    //
    ///////////////////////////////////////////////////////////////////////////////
    namespace adl_barrier
    {
        BOOST_PHOENIX_ADAPT_CALLABLE(assign, boost::phoenix::stl::assign, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(assign, boost::phoenix::stl::assign, 3)
        BOOST_PHOENIX_ADAPT_CALLABLE(assign, boost::phoenix::stl::assign, 4)
        BOOST_PHOENIX_ADAPT_CALLABLE(at, ::boost::phoenix::stl::at_impl, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(back, stl::back, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(begin, stl::begin, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(capacity, stl::capacity, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(clear, stl::clear, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(empty, stl::empty, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(end, stl::end, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(erase, stl::erase, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(erase, stl::erase, 3)
        BOOST_PHOENIX_ADAPT_CALLABLE(front, stl::front, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(get_allocator, stl::get_allocator, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(insert, stl::insert, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(insert, stl::insert, 3)
        BOOST_PHOENIX_ADAPT_CALLABLE(insert, stl::insert, 4)
        BOOST_PHOENIX_ADAPT_CALLABLE(key_comp, stl::key_comp, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(max_size, stl::max_size, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(pop_back, stl::pop_back, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(pop_front, stl::pop_front, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(push_back, stl::push_back, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(push_front, stl::push_front, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(rbegin, stl::rbegin, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(rend, stl::rend, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(reserve, stl::reserve, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(resize, stl::resize, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(resize, stl::resize, 3)
        BOOST_PHOENIX_ADAPT_CALLABLE(size, stl::size, 1)
        BOOST_PHOENIX_ADAPT_CALLABLE(splice, stl::splice, 2)
        BOOST_PHOENIX_ADAPT_CALLABLE(splice, stl::splice, 3)
        BOOST_PHOENIX_ADAPT_CALLABLE(splice, stl::splice, 4)
        BOOST_PHOENIX_ADAPT_CALLABLE(splice, stl::splice, 5)
        BOOST_PHOENIX_ADAPT_CALLABLE(value_comp, stl::value_comp, 1)
    }

    using namespace phoenix::adl_barrier;
}} // namespace boost::phoenix

#endif // BOOST_PHOENIX_STL_CONTAINERS_HPP

/* container.hpp
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
*/