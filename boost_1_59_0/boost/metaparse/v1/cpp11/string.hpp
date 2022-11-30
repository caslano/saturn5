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
/o2FgsExT8nDIu2ra7PnGsQ6cg9Mc8ExKL75IYJdODC0T3i8ddHrhhKhxtX0aDkkoNqdtiO0ws9Q6rhNQmoVDIkVokTp4r500CE6+h5DhNzO/m+a4eSRJCU1Oxd0sVMq2rdsGmjW/atJs+U+3Id1FcctzWSVZoLIxZRrbx1vzXn2+FtssvFwCFg+SqrfaZxjHaTrJNNDgLRQ2sgVSMKr91kuqu74jS6r7PWZT5wsppQdXakRDu9Ztoi1xR++MvuAMOqSU0Ep2EOjmwVNvdv8EsjwnAwz0HASXmQvnBGkizsQt8uR2RCjaqEGYgFjSpahPUvr2YJCFIyj+4hrC7YTF+ZwJ/Z/kZwfqyLGnrRGr8fd1jXcJjk9K9GDaiGNyayXUCmprod8KTsTUbqnvJIKdt8KjLTGel3H3+GrhhKWpw0JtRieV0dGuZgJoULaKU+Gdz79Vg19Es/PtGfk5diOX0YAwfIq2144YAPPyjCthCqAmbTrzwf59gn+A7uZeciEQedBXH0ibiMXR5o41A1mXzbJik5oroXZ/dQoSsvYLD/zEyXTKv/BFBYvRAs/rBDWGCaI+8rsq11v8tdpk7e9PKEjdEbipc3RG/4JOPoRWveUjSn7Zblzi4+sBNYXTlvkfQI2kSAG6HdTv7NKGcNpV+Dk4Vntbgfpi6crDSE+G1dyqFXI38gJalcq82YoqquIolYBfuG+vsRS30pPOnivxEKbnhu2zWtz7BOg7ZV0OTvSJUOOoArtAeu+eV2ZQizWwtT7bH0gggVAoGCUtJxxYYstt4Z/7I3M/W3lBEt3WHD1ziDyzDpv9+8EeyFzo0T1BjQ8r6dG/PekvIP6iOwsB0Be8LjBN7B1MmQ92XuyPmJT8bmcSi8yMxUSkb5/+xJcXNIcQGMfbQKdVkzcSxYLA9fOjfI6m7IwQZ3igO819iMf4R7qJ7ULna7J4I7R0Icuv2KqrdhcoHlj4OOjxHw3kwj9O0MHLZHtjcNHh40exEXzMrq9r5cdStnBVBC2Q/YqOCeQ8ULQ8BTQy3idCV/JpkxoJEWck+q+pmyKCnXfvt7O/gS8qK8b5Hvt6L6O+7F8gqqCegWHyu9vI+UpVukdjTqydmpSRnhChiq3ZgFFP9eOgfcrwpkG7x0xIrytJjk2E38CgM0+YULXPNpEme6UYBbanl7MXcbPtaq7x9Fl0JTjeOq1cXxXplX128gCV0foN7LqBgO05xtmRWb09BudqiDb7dkA46x0VuZ3ChrctbE56wIZVdFy4vKJKMFeqqEN4sjc0sytVNQakxpq3cr2SJ9Yje+VmR8OLyCswNWr3nXDeb6uza6azab/9UuD/36B+F1cciOoVNVXDzZJH1KvQ6VZRbSBCi4qlD+a+k6Bjg/PErniW6BjBiHs6GXHuuKEOHOvd/aNrMgsgo2ws7AXMnAEzitQUExLj3G4qsvun7S9CGT1NDQ359S9DKEqZAprOW7/3PZ7oGO8td68M/s6eTHKhn/Obp6ezSXKZWULqWXAcB1L//08ZHTe1OIl0gBq+W4LELgecHLzNo2KqnbDHRXhs0ciPSzRvP2LWNtXORm6U7kraip80hn5N0PxaNipOOiWyJKo71Zd6Fuv+vMJ+ktw/GRWsqEbV8d3gHlaUltYRKaWJaYa3ZDcLZxTcubhpd4M/o4QG+Kr3c1bMRlaDbLLz79x4espJBfODl8OIaTSgsr/1QGtpMwJ90C+u1zU/jMmJ/WcL2QDH1Y8Cp2Dnu9vtIV5m9/x65huUKFjZZcIWukFOHVKx5aEbD+Jy58Awo2H7O4Z6NmPxkx+7qkaTxKrWdriRUxLPE+HwoOda9RV3trU6w13oI6bxHNOFZVBkPxtkJnIWrsiB4gQhcP09gY9oEyMkFLjybmJQ5Km6WfkUzDhm7dz1bAVpkrQ/iiW7RYlrnuMBBb+/okAnzQy+4L+fiv2T3zw6f1mz91IT8+UQZyUg6SlsQ4rDK0xMhKu6khM//WKLPhSK9d1hHSHuJzdWvDYNQk8vvmMtp/9TmQXN4gkkltV5gJeX/LVYcaNF/BULlTJHuigcODRxxVnUWOO842NYFibai1g/eL60ieNbwAe7fh0bPW478YlJxpCzTBceo4xU73T0t3RXXwoLlyKVUD+dgGWka6QBTEAiMeC1XO3Gvw9uaNqrU3HTbBotoIFkI6vh/LZF7l8CfRC5jE2iAxOelaTZguiPkOCsJvXUdU9S2cfDqHupAwTzrslXhECwB8cdv5Cj5Ap9BW1lWpb7I8klyLb86cmyNrcbNlttGPuP4j9usfBIAVLriPp7Yvd3jQ3eY+si7KjorvKtQZAygbeYPcqQzewATbg96TqEBznWEXn0nFIlPUp+yfxMz/dsILKtk41EON8a4kc8Wgv3wCRPfbV6d5txdb6POENQD/LrdkChVM0xbqZgCDxwIP6FNSttXz6lO9pkw/TlFsxXn1Obe9VcOttii/xtfWODr4n1fhYbLRWsBRLJHXp5L222+xNOlSSiKI7krSbcRC2jHFDg1aXdLAHtPvEb1L6Iy3OWDxd33G42O+3TNXNO2jdK1a4eiwHWbuXcMOGP0ddwtJNpwy7ntCUqZBJ7rAZsvEqDleyRjOIOYNparOrmGVTDi5JSd6OnWPxX/RUaM0IoVcq2keU7Q2pdKuVxNb3nWB08tR94qX9D4t7yuH9AhlFDpjtaI2yvlHYF77zUaktvprlr6HH2iu/2vmDvinjltnnS0EkbZz3cq6ToleDrWkCNLx4SvvDs9GvJUd2jzU8iEBKZe+9iyrzCxp0xKkhp8yACQB6g6lXiEIRrIP8ujXPaljkZCLiXWywbY3Bqx6MtXAOtLAtkkE7vubd/ngSHjxc8XMmFm5ALHmgBexXcJwjaVg5NjEj7qUAu9uHhk2EBxe8OSr8+pO+iF4g4xradMiNvJSl2zZP6LQmXOwTOjXolen6dvl8luoBenre5K6FjiqzOSfhwxdCcSg6HNrKYTUTKlrTJB6zebcd0Sop6K8cepw2+PXmn01QV2OrZwsHpAd+fhS9p7ZXW5V4+GQnejH7EVYqwqYP+9ME/0U5rHFEABVqI7L9goxpsWxgG+8+BHRocSwskws4BntAqwdXf4SpNwaqf+B0WOkDC/uCDTlJEaSsdb3PP7+DcnyKhnWk+B+FhVfPmz348Bcvy9yI2xsQ1EmV4ALHCZ14eZQpb8D28tpQg+xnJht4lsKpiTDeoiDVKibHDY/D2PWsSRJK/UlqQmlJDMvfTvN11XUo4kY+ey6XY+af0D3AoszFWTZSXN0kMpRPNzZMDw6E6dvmaFrJGTflM2Hbo8xU5cQxmlpzqz+l1/Lin2Iy/wHS+OuKt1alIzokWXTdHjrnMK4VciqDL05EZLmPdnRCQZlu9IymNUfGjQW/7V8UvlJTOGsGIbkSd9JYraustHzdne0AGLOEBey0eF0WXopWgf61626mM7GxTpGk3aRYPh3UIrKZx9ba2wqY7cbHhFVTMvQlhWt0fML4qFirjSF4vBj+0RBroRdjXLdtUVZNdjymThS3SMLPN1dPkUFUelsNMKjPxhM73JiJqpcl2+cjZPeoNxhdMTuheMghOvcNAx+wzHUfhvDlgzSVTW0OnZBDp4D01x1bHE1CUjtov2IV2SZ7aX2c1l6jtZ9y4j3ezIGgeLCJlpyMu3gSR5uNL5RTWC/I7IEwly4C0EcJdRuwOYAvl9U7Ba9H3oPWzlqpnbd5HJviVMDkrgNed5Ejw4uLVyroCdyB8+3w44jWHRrdjLZNBqB38dwHm3OL9fo8+86unK/ugfSLlncxloSxuxi3MLmBq4hIpEk7s813nNy/zOpEXF7nBbMuSYHGcnYOSKV2ea8qO2wkiGBK87zsRqKmiqbat6yAcUg8FCJ3aumGg8zFgV5gpa7kSOTrOnodBElLUMrLByBl9z5PDRcSVE5lLPHtypM++I0bQCvoPTYre2hbln5zuQDZgMAJifcwd0GUs7Wrx67gOSmgYPxRdDgPkCjVjgWNTM0GX4doX5XEpajTlBnmXh+ZVx7DkeGPTMCt/pcZqXvVYNjQutU+6Pr6MrNDecsrWpaBkkgx2rQfEqoBJJjtXzLWQ0pw8V/kuLCacMBnaGGl33BkiKUKiVfg/aTxP7UgjeZX3Hn35DvlPS/47JJg4eEAdzs1gl27IHO9UM9ptYy8GpExM0PEy7rxELcODCNjkk97o6d2ZZ8bzzlx8gig+H/gBUnnn28ltm4IJcr0aG4dq+OyyCVDQirFqisil0V7zY0MpNNOi4uEzj1e+N7NtwjaFQMoLf2dYc7sSAmiSRyVMXWkpcR0C8Bzh0B5+4IT84NYiJGrETJHusMNjdDbDasbU+W3ZsZOorrlFvnUoBM2/1c4UpBxSutc2NbIUcrEUzLA5gUrgUqtttDhZ6XuVXnV9KYsda2aI2dusOKqpT/gnOnSUbzPEDqayV89aOa0UKMQfdxKsGVYy/8MdOSkzR37lStwg38eob0e6+gx/KX40pes1O6DPQ1ddUcWWrIe4G3ON8wTx7J6TSF2Ng/CjkW6gGX3q9LHCyh+hPwKq7UhRsMdzAlJYNa+kP7VAZi3EfnUG5pyFsHFpZK2OhlOhZSR9YTod5EqhK/idJd84TR4qtKQK7EnH8fVMjDZzjk47fSse1tDQm+zTArTSiqmbNGD6LPqkoY1DKR2jWVoHsggPab/fhpCbIq4Dw9aPiAjHEH2g/bN95ZRs+6uoHPVRJ4kqjmP5sEkK2Vz1ooJzFrgqeu/nZuVatUsOHOA/IvZINtNLbLBog9eXp2qoDbrDGnMsLFg8EVDfUYrM7KxkTFJkdPq/f4js/nLnlFEvfEEpj9wEHgpb0g1ZyIIi1FDIxCBee7WdRsbc0/g1o7BBAhsAiKnjR5Af0E/+LdXwNwLeIVXw3Ro2VehTwROpFuC2JO9GOZWyBXbrVRc3VNsKECXAODavLVt27Ztt7e2bdu2bdv2rW3bbrf/w+bP7iRfcpJ5mZkzOZl5Oo5gD68p8j6xyAkqYNWf0ClZGgeKMJPnxBNnBnKMTdlV8RAMYvDQhfZg0PYg0JX2wmJ/FfggR5pNUr1t0MI94bBUwdlKgW3QqgZVKPOqp0xjdcmaiLqfuq+XL5kX6dUpyotvUaVzqQuKr8agsknB4m90N8oIqjpwnRTmJL69q4vTtUrhL2B0EadkYCDvTWkEUuErVCirY3N4QCsLbSMXiVJo8cXLhrJepRXYjNfOc2eo9lHEDXTu0kJjdWwOeEDBg92ILjzvYLngt/9lFPD3me/RMHM7Ty9STjb3Ht5fY2JkYM4pkxr8IWX4m1WgnMf0Bg7RBmkYg/iHRtscP4Y9EnY+jARBAnEFkw80scWBT30bmIsWr2yov2M998p9iBuafzRhhErLAtDBDk1sNieuBmJIypzKxGiulgRZeRABk4fajYZ1vPQ8452vB4Umr0u8Iwa5NVi9YM0TnMvHcYsbZrBFAPYd71QlnP8D5CkWF1zlPW7ji8EuwptJ27E9LeB4kU1UOjVZZ4aHKhQmjXZt/8/a8HoP6jz4mwx5B6/07T+nLBDhHfmx4RedbY0oAhzMIjDzy5SDmdMIh5jLcs9yfHR7e+84YZFP1++Oli04s8lr6ffENF0g0Gt+uCNoAAAs/9MBn/cA7NbXNB9dvkJ4sJ/qHs6gInepsPdJmz5eGj3yxbmgnZIqouV/yeKtsIrGxylTZcq5FrMRrKq01Wq1y6IOo3g3lGIFlnh+2eD2DiPrENCY8kcVUUbwx3m2Mp7miWZO/47+kJFbJ3bbo3ZzIFGMzktCOG8ze6S6dtEwxSM0mKJvlbQM/mUZ6GbFd5ofjcDtggjSTN/p2AED/KgsDi9sGnIJnG/xMRO0pLGFwOnnK/2LIrQbFiqXkDjPYDHuD4GKDXh0dksDOnZgjHtM2z71U9IRxAzsUAei6PSjlCFZ5ScWNzKgBXWputl7HTEeUggBBSeyRp0y6wCzk6Izc7G4HpBQ6POheFiv6725IlonCUNfpxZ/cZ+OZVd/yw2ZIuEpVXZo+PdkrA3Ws3EhD4WVtcivfVARRH7hr/TymBLonxCoRPcrP7/Cl6MHwdaP5b8tLB8XdiekT8dzmTYso2+mxSl5bIfyBcrnSQurKWtMlBHGJkryDjVEfHvmoicjc/oSGVf+rdvEihyxMF3DM3KoJxrTQ5yZqpfMA2u2zYghT0sy6UuHG5DcN8j1N3912BpOx9Toe57Nq9Rp3TH6uF1bitMthePfkGuWHNpOx1PuG7H1TCjDbXdNtA0wOp/VW0qz/b6PuK/4KtajUrPFGVB53yZjFcXwrVNplFY6Jo+ULspGo5FNJUKnstPg9DyFL+GcMKTmS7r6m18zIZdlKu6iG1v0J+D/4KtyuYQkancyUTY5o5Bcj/M+EWgDzIs0XoQ3Zpp0iPT+A8X2BCkd3KC7EArj1zuKHlQdEoJ6c5AFj2JkAzbFDXdSRTCX3HWNa6BmG3ZP7bNLYiaOLmE0avMgKrtadmk0ISQ6KRd8ngAblrGwcZbS2B5CKinbSoamDn8Pa1rMtnNugjppTO2hJo+FBWjw974um5SPnFzm7iJzXzcQgJ8I1p+QME0FDMee1GiRM/tjcEiX0xhhHc3YWy7O3Hw+JOngpgf6PDH7lKdj+UWbCpE0jtT97N7FxTDvyv0PIiwG82ggf4i8GhoLhS5ZQXtvRMFWLQinUK7FNdbImX+OF2gVhcF6lsWajv1A8agzIB60APGCOeeS8NIb95GadXYoZQAzKfPJrZhWQxYEp181hLHA17xP/gBss1Nkx4FnrHAW4uO5m4Yii4vzywTFvEj5FnGHa8nEOC84botu1zKnYhb6ZfMP5Lq4brLIrVhzV1dATpklRYZEKIhMFiNLdo9MwARHmQrAGy3H+z6M+F9nrBZkmmhbWNcaa+kM9q87G84Z/J1KpZiz8lsWsKhGuSkr1jWq+eSNYg/Bv77Hgvjo6/LQMlgDKSGoHgxXfJOSNZbqCbOC6xS0SrcDzajN36rDj3mCwl+qodfz5wbDErACU6y7U2+8h2yDX5FaqlNYGS4sM44r0KEX2bktrk6NUNA100C5Vs29rpMjxcMhFXpmKeRoJH90HP8xT2DqgAv3KnqI6pU4d/DOZ8sEpEiDmZoU744HjLwbwsl4uHTa74c400JoQTbqlWuGTYdnSjRU1m8NZslU1E0Sl2T1N+KaARk6fsjejEZCm+ftaaL5banH3UeYqe7z8++7faNLVGbClFLE/sPQdsfrC4bEslSJJ0Z+OPMC8YLyMD8SK8JapPBhq7r1vtpgfhs8xqy9RekvtjxOOZCudtHTT7cO1BzUrMwOKVByVJaxqi8K9V7oygT2tx/ZqoCZg5QAOAHBXVXdcNG/jXlZLa68Errqye0zfjGb5y9Eu3zEeupYVu8DEOo94uVHIYcoWSX9lyGK8LVPeKzjleci7bvMTJ1mCVwdAgHBBEchcR1b4Qw9cwqzbQHomqUCrJ6Z3gjAIs6CluBdJhPaK5/dhDHDWOZFHMqP9bRMyimlgjh/lVfttAKtZc9XQKiNksigeyY1AC4bgncqHf33+XDjzNrYoXOV6mMRIzKPapNhuKkR8z39ifPDRqrH
*/