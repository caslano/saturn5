#ifndef BOOST_METAPARSE_V1_CPP11_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/string_tag.hpp>
#include <boost/metaparse/v1/impl/string_iterator.hpp>
#include <boost/metaparse/v1/cpp11/impl/empty_string.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>
#include <boost/metaparse/v1/cpp11/impl/pop_front.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_back_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/pop_back.hpp>
#include <boost/metaparse/v1/cpp11/impl/string_at.hpp>

#include <type_traits>

/*
 * The string type
 */

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct string
      {
        typedef string type;
        typedef string_tag tag;
      };
    }
  }
}

/*
 * Boost.MPL overloads
 */

namespace boost
{
  namespace mpl
  {
    // push_back
    template <class S>
    struct push_back_impl;

    template <>
    struct push_back_impl<boost::metaparse::v1::string_tag>
    {
      typedef push_back_impl type;

      template <class S, class C>
      struct apply :
        boost::metaparse::v1::impl::push_back_c<
          typename S::type,
          C::type::value
        >
      {};
    };

    // pop_back
    template <class S>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<boost::metaparse::v1::string_tag>
    {
      typedef pop_back_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::impl::pop_back<S> {};
    };

    // push_front
    template <class S>
    struct push_front_impl;

    template <>
    struct push_front_impl<boost::metaparse::v1::string_tag>
    {
      typedef push_front_impl type;

      template <class S, class C>
      struct apply :
        boost::metaparse::v1::impl::push_front_c<
          typename S::type,
          C::type::value
        >
      {};
    };

    // pop_front
    template <class S>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<boost::metaparse::v1::string_tag>
    {
      typedef pop_front_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::impl::pop_front<S> {};
    };

    // clear
    template <class S>
    struct clear_impl;

    template <>
    struct clear_impl<boost::metaparse::v1::string_tag>
    {
      typedef clear_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::string<> {};
    };

    // begin
    template <class S>
    struct begin_impl;

    template <>
    struct begin_impl<boost::metaparse::v1::string_tag>
    {
      typedef begin_impl type;

      template <class S>
      struct apply :
        boost::metaparse::v1::impl::string_iterator<typename S::type, 0>
      {};
    };

    // end
    template <class S>
    struct end_impl;

    template <>
    struct end_impl<boost::metaparse::v1::string_tag>
    {
      typedef end_impl type;

      template <class S>
      struct apply :
        boost::metaparse::v1::impl::string_iterator<
          typename S::type,
          boost::metaparse::v1::impl::size<typename S::type>::type::value
        >
      {};
    };

    // equal_to
    template <class A, class B>
    struct equal_to_impl;

    template <>
    struct equal_to_impl<
      boost::metaparse::v1::string_tag,
      boost::metaparse::v1::string_tag
    >
    {
      typedef equal_to_impl type;

      template <class A, class B>
      struct apply : std::is_same<typename A::type, typename B::type> {};
    };

    template <class T>
    struct equal_to_impl<boost::metaparse::v1::string_tag, T>
    {
      typedef equal_to_impl type;
      
      template <class, class>
      struct apply : false_ {};
    };
    
    template <class T>
    struct equal_to_impl<T, boost::metaparse::v1::string_tag> :
      equal_to_impl<boost::metaparse::v1::string_tag, T>
    {};

    // c_str
    template <class S>
    struct c_str;

    template <char... Cs>
    struct c_str<boost::metaparse::v1::string<Cs...>>
    {
      typedef c_str type;
      static constexpr char value[sizeof...(Cs) + 1] = {Cs..., 0};
    };

    template <>
    struct c_str<boost::metaparse::v1::string<>> :
      boost::metaparse::v1::impl::empty_string<>
    {};

    template <char... Cs>
    constexpr char c_str<boost::metaparse::v1::string<Cs...>>::value[];
  }
}

#if __clang__
#  if __has_extension(cxx_string_literal_templates)
#    define BOOST_METAPARSE_V1_STRING(...) ::boost::metaparse::string<__VA_ARGS__>
#  else
#    include <boost/metaparse/v1/cpp11/impl/string.hpp>
#  endif
#else
#  include <boost/metaparse/v1/cpp11/impl/string.hpp>
#endif

#endif


/* string.hpp
E3HR+z7nxbuNR3Dbh/CNPvNzpBPr88R7d5/7aR7Or/Je4l444xFr9bM70/unHPgv7ZyhcElfqjCeJ78sJsK+y9viEY8Ll8QPF+hoc5zmB6WCXPd/dlV6d/JQ3O4TFTyGP9fC90zM9O0P9d4LqzIze+k9KrzocGQr5o2/Fvrp8qro+med8WQqIdZe7BysmmDJTDpZoPW8YK+ihmDGPKdZk8UFnHg5xWeTkH4FcEnp2zntVpxbvMvZmzCrPqmsr9/wTbRJW0vPN3+nbN/SabBDYJfVVbvxfwxsBcz/l0b4oLi7xc1jg8rjTyhzg1znhS1KMD8Odvu9kNe/zieT0fW26f4m5PzvLWINB+HlCBvcfwrcoupf98t5A+j8RYu7FlTVirMFrdFnC7RNVd0q+itwNla75S9DnsuRJ9YhrJxhvZq+3XWIY1v5jhrWjfgOV3VEGirpuFa333o1vA+j89B3cB7Syr6CNO5q5y6WTnusVztP2u4F0q6itJspbY1OizpGp6vx1rSyvHUjrhuyeEIr9iRUuJt9GaHN+MyGbteT0WYPVW22nsJLmTanzR5GcQG/NZ7m9yNa5dmfqPxIx6n23FAFf1IqjaZjE6UbcXRZIUKXFSJ0WcHurrrrzQV/id7qK+yltkp9ZU9bot/im/qt3K87gP63BbyU+055NW8d4jVTrE2yXMg6no423anWCmaqWR+hLTD357beoNqiHnk9sZrlw/Cd+Iv9afCd11xpXQhrreIM3HbIzKNbI8bQatxN4zHd8ncj/3XHefq3Cfk1I78g/UbUZSO+n2jTM482In0r0re1inVjlKP5odeNOyB7T0QZS0iXSJ8bs2qtpJvw8V4I3h2ZTI/l1X4HuUKhxbvw3F8vy5HZIyoczo4nbKpg9ueC+M4Tn8soyHXDh9YaShIJgs4kJ7ZZ2GqbN8GsuO8P95PWE25tiNvgdUC2Y4Kmy/icQIHcAib341lYBZxnPjs5gb23oEYMEPPZHa3ufHYnhU1a954gnUGlUt01doJNpDIEC++SDQj6V4Cns8m044ZhDrTcmYdF1N/IyrmtfK8UdwFxXm3/ZCJtLiZNJsexBmpwawx8fz5XmoHdWEs2nYFNYg8L6V9oYFTVQn7ctukuSnu5gRWsIXWkEXbUbqmXqmzGJDwZKtfSLQEh70+ATRBZ/0Xwz+Q1rMaKx1KY+hj1B/op3zMj6JtxpMH+CuHD55vjM2iS2p3DNXS3j3g/Lc8fj7ba93zpcH2W2Cn9IiUn3DtiJDAmDDlbZ89lEQ9hJ+8RPFxfgfxG7vNV2JfzqPN5tkwbFfqZu9veLZksZce9sN4rbDiZl/vNteacuFO/gjN/eKyto2kr/6254BzVPllP0HsgN8bUMqB8/64gnWnjC6gsrNXSN+8rX2ThbMc8DuPQhfTXYD0eMpIAnp+G1w6TFi58/VKYfo6dPo48JlRZVIb7bgzw9qs8IcNOnmlhez1W5XNxYNcg7q7auXOLabaTBI7Cxdica9X9ifDwk/bAE0EH4cAe4DJUP6S+4pZRtGGsfcIfC9svfLZ6FrzpceR2Il2YSRbHp9ifruFtjb1/S4Lg7IFaT4epCSNP0NeHpc6CPGlVI++c9cz/hmR3/PzB3sQ5Qz029VxwKJNPUmPOky0dRC+/YYU7xP66Io855IbNB4V1eErEmGNvKqMSDJlnD6mCuhu6nypsyMu4raPzrIAWk+fTVd94hpLpZwp5f7KKe7bos6AFcoh+pfrjJ+CfjfJx34FC3hcq/Bdyf7KyeQjzCqz92/nli9F3XyL0xIXK5nsphYkmO3ck3Wrz0O+9XIF8zlP8uDKkCft0XGfwgOmR/eVVgp5jT3DzvEo=
*/