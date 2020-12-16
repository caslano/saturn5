#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_string_size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int MaxLen, int Len, class T>
        constexpr T string_at(const T (&s)[Len], int n)
        {
          // "MaxLen + 1" adds the \0 character of the string literal to the
          // limit
          static_assert(Len <= MaxLen + 1, "String literal is too long.");
          return n >= Len - 1 ? T() : s[n];
        }
      }
    }
  }
}

#ifdef BOOST_METAPARSE_V1_STRING_AT
#  error BOOST_METAPARSE_V1_STRING_AT already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT \
  ::boost::metaparse::v1::impl::string_at<BOOST_METAPARSE_LIMIT_STRING_SIZE>

#endif


/* string_at.hpp
JCTYyzUMd2a9Bjdnsf4Dh7rfgyPV7a/eZHy0z4471O30Trfqv7z3LQkGfH4HvXcnP7DbzXvlVVQc0WtdJ4s3Y/rNuEjGnv7JaqUX4MMAOmX6ELVvCv7/ko9z829tMS52vqtnzVKuF7uNrWm6BfF+prXjpqXkJT44mqAOzYmz/VwlV1YXlM/02ajG8f1x1vJftmRN28cxd9pY63P9+aEd/8GdifDkmFr66gZ6lub9dXm9flqvZVsYliLeYWUjOLLpaXOiC6Y/H88Ze32fDxn3puQ54Ht0RGaYUOAG+R6vGQrRY3pJI4f4Hl7pI+Z6Veen9WJtQsS96XpTtEa/vDQSrd8Gd9w07Jd9a29kMdfa1sjb6y/cC78T+Q7+XQ93TnSxh5jumNKZXV6kC9JgzGD2ptN+u57tS+l9vOLc9j60tX9zzCQ+byAv5eAX1kC+9N3DLfS96KVtP9lfnmxP/M1y5k79Qj7rM0WtnsIml9PfdFBHsfb8S3xbTk84Xa/2ZjXSFfRNZ7pe7V+svLW938fUBHp1+KKwvI/o483uBuP74/oP2BbfrKK5B8HFEhPs93Lf5ojVcP1NudSK307iXLj+vRh8bDYNTiOVFWcVN7gPDg88rDbqs0jPX55UOyy24cL7X8Gl1Xh/Oezx2cR5uBK2VMBTtbLCZ+soJTtYxxpiPRIuFh+OH+n9flfTrNXkyfa4HqLpk6y9yN2PyxnzY3CNxunzY8joFd7gXsRW/H5PG3X6BrxxhO7Eb0VyqAFosBz2QR/SP8us5j0xCn6c15sTt1vZdEwLsSV3ks6p6+pYc66kViyJj3dZh0syruHsyRbf8X3l8nC5p563XJk7TJ1o33B7/LOdPfrQ9OkDrMsZU0Vzet9ei+T3Ihl7+I/mEEuu27qa+mmkfgwdWp1N/siPBXPDzPg9bckwR52XTZ1VRwzkudtxsPsp/c8RLWnGsupJ98t1TqK5blWT12fDmeryp2DXCHW33N0Ad89dqZ8i707C6k+sERVJx0fx+5y/whvGMko+z0q0tyga1V+jGZ6FDzVowALWv5Jxd9d4zolz/agRMKga+z4uRk5lg5u74OMadSVMzpH4y/23rXuyW27r2H6/Rg1ZZprY1r/aucI8Squjg7gRR7uv0vvGAWXmqmPFZRVjznUat6TinZL0zG+NSd48X5YP2oj1gnJstVy8T3xYe+rimL7ir7/jR9B0HXfq3eLdXXDgozpynC5IOS1H1YAdUiPqGH3OxfiEdrmrAGyvrp8K46+YKMecd89dsK5P/L5+60DPWxdbRQ/nENPD1HR0yhC4XepbvUUxm3WFedGDt8uB4rfRL2l0zHR6RF5Ura5/rN8XpaFPnOGzj+EufT1Iv3vgOHm3nlZmq+3t6E61cKra8UAmfa8utKwYLhrfl90Hz5dmg1b0y73i9xEa83Yx0hJe8t3c6nBoll7RMXn7mnnsY3vzfPNdfRp4vegLc6il59NEHbYCLz0Mj8bDHbm+7nK1SR+1XW75tl7c6qdUFFsH+eu7FvF1WRiTjp9gYiY596Q1gg1sfPoxvtgtjq6w1paKm5ZGM3qkExuxRUx9opezKc0+xwfVny1wnthc+Qf1xwx1zFM4+Fn5Ty+PyGUvrzG9MJEOTo56NpQcfEPfwRhKf0gjTGdTXF0tzTVfV7feiOvVcQdw9I20/mj6v09/sYsneuSD3X/APyf0GHuLC8e8wr87stKDv5OX7nPLMtMxy+kYvqzSyLWseSZ8I9euh8XT2Dgv/65kz5nqhPzWQ+xZbJ7IDnBuVUH9EnnVVQ0xkk9H76HNHZMcf7+sObeeByOfhy0FxVFWeyv4PEmcjIEzP/d3vqIwAne+3EQ=
*/