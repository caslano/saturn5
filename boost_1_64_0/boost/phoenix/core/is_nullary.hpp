/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_NULLARY_HPP
#define BOOST_PHOENIX_CORE_IS_NULLARY_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/lazy.hpp>

namespace boost { namespace phoenix
{
    namespace result_of
    {
        template <typename Expr, typename Enable = void>
        struct is_nullary;
    }

    struct is_nullary
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::fold<
                proto::_
              , mpl::true_()
              , mpl::and_<
                    proto::_state
                  , proto::call<evaluator(proto::_, _context)>
                >()
            >
        {};
    };
    
    template <typename Dummy>
    struct is_nullary::when<rule::argument, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::argument>)
        template <typename Expr, typename State, typename Data>
        struct impl
        {
            typedef mpl::false_ result_type;
        };
    };
    
    template <
        typename Trait
      , typename Expr
      , typename State
      , typename Data
      , bool IsTransform = proto::is_transform<Trait>::value
    >
    struct is_nullary_custom_terminal_impl
    {
        typedef typename Trait::type result_type;
    };
    
    template <typename Transform, typename Expr, typename State, typename Data>
    struct is_nullary_custom_terminal_impl<Transform, Expr, State, Data, true>
    {
        typedef
            typename Transform::template impl<
                Expr
              , State
              , Data
            >::result_type
            result_type;
    };

    template <typename Dummy>
    struct is_nullary::when<rule::custom_terminal, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::custom_terminal>)
        
        template <typename Expr, typename State, typename Data>
        struct impl
            : is_nullary_custom_terminal_impl<
                result_of::is_nullary<
                    custom_terminal<
                        typename proto::detail::uncvref<
                            typename proto::result_of::value<Expr>::type
                        >::type
                    >
                >
              , typename proto::result_of::value<Expr>::type
              , State
              , Data
            >
        {};
    };
    
    template <typename Dummy>
    struct is_nullary::when<rule::terminal, Dummy>
    {
        BOOST_PROTO_TRANSFORM(is_nullary::when<rule::terminal>)
        template <typename Expr, typename State, typename Data>
        struct impl
        {
            typedef mpl::true_ result_type;
        };
    };

    namespace result_of
    {
        template <typename Expr, typename Enable>
        struct is_nullary
            : boost::phoenix::evaluator::impl<
                Expr const &
              , vector2<
                    mpl::true_
                  , boost::phoenix::is_nullary
                >
              , proto::empty_env
            >::result_type
        {};
        
        template <typename T>
        struct is_nullary<T & >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<T const & >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<T const >
            : is_nullary<T>
        {};

        template <typename T>
        struct is_nullary<custom_terminal<T> >
            : mpl::true_
        {};

        template <typename T>
        struct is_nullary<custom_terminal<actor<T> > >
            : evaluator
        {};
        
        template <typename T>
        struct is_nullary<custom_terminal<boost::reference_wrapper<actor<T> > > >
        {
            BOOST_PROTO_TRANSFORM(is_nullary<custom_terminal<boost::reference_wrapper<actor<T> > > >)
            template <typename Expr, typename State, typename Data>
            struct impl
            {
                typedef typename evaluator::template impl<actor<T>, State, Data>::result_type result_type;
            };
        };
        
        template <typename T>
        struct is_nullary<custom_terminal<boost::reference_wrapper<actor<T> const> > >
        {
            BOOST_PROTO_TRANSFORM(is_nullary<custom_terminal<boost::reference_wrapper<actor<T> const> > >)
            template <typename Expr, typename State, typename Data>
            struct impl
            {
                typedef typename evaluator::template impl<actor<T> const, State, Data>::result_type result_type;
            };
        };
    }

}}

#endif


/* is_nullary.hpp
xXfrQSSeDcnC7P6Zf+9sTrZNR9QgvTmwYO2e9SmoiOcqMgOzz2If/Yr6JHNg5hKahfHMILNklvflXCucMRXrZlunCt73KGb70N4a71vJzJlVu9rmY6xZZJWYdey+LQo1r1hl68UtcKZV7vcqY/4gzAfF/vg4PhhnIjIrZoN6eoci7z11OhtmNWZ98CVyS8bbdTi4HWcUZzJ+v41d/7iO/YisIjO7jj+/whxT2s2Yfq4b1l3F7lT1x5j5kvG8O/SrfQ+1pNzv7u5i7MUBZHw8c67cwf4QpLSbH+9+HvNW6UvkYHesn6OVcdmeYP0zzoOKDdh2Kw7rrnK/CMcGQ3GeUO7XcchnyZrFKrHX839xA/NBsf7Jj29jPij3cx3mgPpMUMyhWju8w01S+lJ9QgjmSopyv+gmCXhGT1Xswyubxmu2T7lf61qLVmuWrrRbZD3zR80yFDtZqaNes0yln1EBntU1y1ba9ar0BOOZo9jRxGTURK5yzU6Z3+FzoHzFOud1aqVZgRJf6dMxYzW7r9Rg69sLMP+KFcvqdgi1VKpY8wuZeC9l0cs0hoK5X+IcaUXG24W0Xo391qBY5W1F+GzJkcyK2YWvW2FdciXTM/PbkIHP2L0U21rlAN4l+JFZM6tWuPRbzQIV8z8zEM9qIUp8vcfl47OXUDKeh1i3Gus0C1PahZsNwOfh45XY/Z8+xPN0BJkNs7CzDnjOiVLaPY/tOEazGMW61f4M8y9OsWmW2/E5czxZRT7HhszGWCcqtj9gEd6XJys5+vPjvnhPu0+x4Oaz2mMeKeNy79Yb4zskpZ99Di6uh3mkjPX0oXePY64oNmPjomzMFbLqzEIPf+2rWYliZw47OGnm4E9nG2YNnRtj/fQla8Fs5/T0DppFknVi1ibw63mIj6wzs92RJVMxHz40rUHzxQ2Xa+ZEpmd2bvxcZ808lHZzm1bEc4A3WRVm3gMG4r2Gv2JDKt7G+8FgxWr+kNsWdU1Wg9mwwxvwOVe0Yn/cqToYtUTmyGzC4W+Qo3TFxnzu5qlZnjoujWYg7wVkNny+r32F2IvIbJk9PvzjV5rpepuOZ52bOnPkgYxfs/G/H61EHhQLSB6Is6I7mQ+zdLuYC5qFk1kxc6v7BM8Ws8mcmR1vFYjnqiSySswOvjyAZ4sUMj4uq6Jb9dQsTWl3sVIj1FkGmSWz5ZlL8ZlwlmL7I3tgz8lRrrnAx/875EiJr+ri2qOQI2XMfM91OIIcKTF0dPYuwJ6jWIXqhUuwr/RR8n50cgPMWzLebpRb5ReaOSum6329CeYRmZ5Z9NExeG70Uez2rli8DwlQLCZuKWoiRLF7b0OTsQeQ8TlWaf6//oOaUGz0w94VNIsl43U99loMnpkTFLNcOXIG6kUZs9H3DgWhXpR+ngr6KBo1QVaTWfCyDReRWzJLZrp9Dh44ayhj/fuv82AlZJWY7faYh/OnLgA/V/LeSgvankH+FFs4bEFtrHVknhb/PKvVIJtVpQ/2ad9+2MfeW1DYONS8P5kVs01zB+F8HURWidmVukeR9xAya2YD5ln+jDWSzJZZs7DwPOwPZFWZtQtcnILcklkyq5kS3E6ztWR6ZkubfLUD6wRZNWY+Oz4rQm7JnJgdz0lHXecrMfy1IgLvaQvJKjP7PfrWx8gfWW1mGTeOPMbZrb9pDD3+fDMO+SPjY13Y51ILzD/Fph8yfIDcKtdss63rAORWaXf4eS2MWYBiyfeqYv4Fk9kwa3DmIMZstGLX49f9hbVc6Yv9wg3PkVvlfnffJq7H3qi063vm9m/IOxnP7Z09B65hTit9yXmRm4EzGBnPkbfNiM7IO1l1ZmOtOp3DeYmsBrOXJTe6YE0=
*/