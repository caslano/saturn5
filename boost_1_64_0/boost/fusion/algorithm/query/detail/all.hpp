/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ALL_05052005_1237)
#define FUSION_ALL_05052005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_all(First const&, Last const&, F const&, mpl::true_)
    {
        return true;
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_all(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        return f(x) &&
            detail::linear_all(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }

    template <typename Sequence, typename F, typename Tag>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f, Tag)
    {
        return detail::linear_all(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct unrolled_all
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it))&&
                f(*fusion::advance_c<2>(it)) &&
                f(*fusion::advance_c<3>(it)) &&
                detail::unrolled_all<N-4>::call(fusion::advance_c<4>(it), f);
        }
    };

    template<>
    struct unrolled_all<3>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it)) &&
                f(*fusion::advance_c<2>(it));
        }
    };

    template<>
    struct unrolled_all<2>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) &&
                f(*fusion::advance_c<1>(it));
        }
    };

    template<>
    struct unrolled_all<1>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return f(*it);
        }
    };

    template<>
    struct unrolled_all<0>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& /*it*/, F /*f*/)
        {
            return true;
        }
    };

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_all<result_of::distance<begin, end>::type::value>::call(
            fusion::begin(seq), f);
    }
}}}

#endif


/* all.hpp
spS0fBcHs0v1MRUrSjlXqTm24p5SbAuPQGOMxZOlujiLaozFXmXmOIvZZRJr8XHyKsMGyJmhnB9GxnN+6I6/iCzRr3sbu8Qbh3HOEm8sxtX8/3bEKiZjLd9r4zI6lprXyh2kTRnjM6aRfuxSiDh3UsZo8lnqXUu3fam6no4BVR+z8ehSd9zGBjiA79uWe+M3Di63juGYVq6P47hvp3+xHLeWY09EWafXALVr9SKXudfrJUOJ7aiu3cvmu7YT+d2ylo3veHCZ7xiPXfjuk2X+xXgcsdy7BjB5uXsd4Gq4C0nku1poF/fxxPLWfsd+7LDCHf9xMHStH4RpsBxWaWJB7uP/D8D3oXFNYa8K97rCEQr5nA4rkC6J/BYa40Tuq/DGilRiux6r8MaMdKz0xI30xnztt9K9PjERauNIlq/Ux5Ks4XM2Y+Y6ZBdyCDmJhN1DTEkkGSlAqpD9SD1yBonczFiLFCAbkD3IEeQk0uFe2ggyEclE1iG7kIPICSR0C3EikYlIJlKJVCP7kXqk7Q/5PZKMlCJbkVrkBNJhK2svkTSkHNmBHNoaXFMZPIJH8AgewSN4BI/gETyCx//K8X3E/8sqZUfiuUoIgObF/1PW3+d047ffqOvn49PSUqZcNTMtQRvX76XBDnWdYI34UZ6WtVM1yChlvt9C5V2Y8STzWAhR6tfew8re0d8q59DsHR1nWEcUodurOau0uHSZM8e7bkPW6LinOHnmu0fKHHjtuo32nSSdYc53lEV8gNGULbnAomwBxg6MtFhvV2WR36BwvrfKL8DYgZEWsQPbhlivt6uzyi/A2IFhp+1jEuRZxA6MUeZrW+XbhNiBDosYfWNi0WmRulZEn4cf5/fY8Y4mrBfx6LXaIkbfWKWvLPLM32+6XpE+Y/S55wd2OMc8T/JWHGjVizzzA+NTpw/LSJudnBDwXPES81xp+pZ+vuYpWNf67M8NtJ4DaDdn0G7Omt2cQbu5gXZzAO3mGNrNJfz/mzP4n5obuNc112/nD566ZvW7z/044/GfLv3VM1fENm2u31aHXPfg0+KTC4MbpLdcjHo94CWwL+wPB8OB8Ep4KbwKDoKpcDDMgUPgfHgZvAkOhZVwGLwHXg7vgyPgDjgS7oWjYA0crd1DssDeZ3iRNk5hI+n6aH13kq6tRbreWt+YpOvd6PlkjIbjfKTLlHTDG00n45qMdw2IpFP3Cq4NcfvkEreF+NyHrDlxFpuzz5h5j7GW21/s0PiW21esqXuKNb6XmH/7iNnvH/b97B2Gfwm/UtP2C3P7kpq2T5h3j7Dm7Q/mr3+oakTT4kqa9wXzf0+wAvpmFbIPeR85jfS6j3Mg2fcF/SPB47/3+D7i/2UVND/+n/JcX6TGxvPOj1yM9JK13l8ra61nuK6n0xPSUifE84yQmjx1SkZJ/vxCP9Z7d5T13kmR7mffcN1ab+fCnGXe+A/7XM8zi7Idxrjwotd18vwyEzmFXsnJZr1kJbrPGGkShwu9vPF30g1r0CdJ/pWtvbGI+kgsotOKXdz5J0+dkDo6Y0pq6syElIz46RMzUhNSprD4NDt/fk5JqR/vPTzPkKHhEgspS9ZFqzZRXnJ433FEtRE7aWKTlLUxxVDQxex/WHTfjnwbwzmuQXdvHCVR1n9dy1tQV0897wsxPyufQZkGg655paXOjMK5+UV+PCt7nlNv5GTU67zScnlOVWNmOFmIrrdZYqjMz5N+8AjyT34QnaLTQ7qA7/gmHbXxTaQPlFv0gcpG+sAR0elesU0V4ohFUs06ZSilDKBvopeub07rrHzmJIa2VH6OuR+0RodajQ7KimtpTH63pU87tVxb8ujar41Z19BYzpHm1TU=
*/