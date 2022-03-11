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