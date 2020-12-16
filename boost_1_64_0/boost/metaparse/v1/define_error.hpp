#ifndef BOOST_METAPARSE_V1_DEFINE_ERROR_HPP
#define BOOST_METAPARSE_V1_DEFINE_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#ifdef BOOST_METAPARSE_V1_DEFINE_ERROR
#  error BOOST_METAPARSE_V1_DEFINE_ERROR already defined
#endif
#define BOOST_METAPARSE_V1_DEFINE_ERROR(name, msg) \
  struct name \
  { \
    typedef name type; \
    static std::string get_value() \
    { \
      return msg; \
    } \
  }

#endif


/* define_error.hpp
GR/ujd8o/LzNzq89n/kPJcrXy8Tf4JeUKF8Hs/4dfk6J8rU0+fnxISXKt0ehfL3wAUr56vF7lPH1V/BbTV9Qifkn6/DJjsv6bWoB8y+0+au4Nv6fxbX6U97j0YWe/mWPJ3Ft/xmP5/T9E2ykexw/14mPks/PSfhReNw66/PZ36cGP1L4DtwcbQ2+LNjZh31qj7Yezwp/Hi9+nx/Qf9/og3p+iTiubV/r2T6J71Ni/d02BZ+Ih/Fq68S32fjmSfguwufjlYXS3IRXCv8ON/HNt+CB4zK+LbaI9g1erv12KH4OLtdXNe3bOD5MeA437dtu+FnCx/e09cvu+BC83Pqq8X/QP6rNr8crQuXnB87EvxP5Nz/v7cx/eIT6Yaj8+kdf4KNw+fuY8/8SvwiXv485/6/wkbj8fcz5f42PwMv9PvVZ23/cskT/4Ap8rOOy/2glntTW51lC/GWJ/o0TC/ufjC/D45XW8x9Tby3s/xb8KeEdPuF/Zv4RvlD4VbjpX34Iny78PbwYX/xPvg9O/6Ocn9IKPwYvd/6t8b54ufP/AHevn1wf61P8EuH3d3LWT34ybNd/KdH/+Dz+UcGMnz3K3n97LWX+o/ADPnLiH/BMifrf3oU97P4U/Rt4F8ev+cju/zb852BnX+rs/3b8J+FNPrZn8y7+N+Gj8eLXZJmdH9amRP/mLvgwx+X6OXviAx2X/df34asD67L/+n78Ocdl/3X98nDweonnu5mpP+Av4FHHh3ay85vW4SuFX3yEjf9cjz8jfBlu/rrpGeZfOC7XT40+x/iUtn4ZflYg56/Z69cfP1R4rqszvorf08jev3J9z6fwWTx/hznP32GfcVyzPgl+l/Ar8Ram/wufKPxl3JTm4+f//35zvcfnzvmvMvN78VLnj48P+Hfj4vxPwDsLz37u9B/gFwTl20+v4EOc/k25/+/wQx2X1zfxgr7/Glzb/xW4tv963K6vV2J+K97FdTm/Fe+krE8WvMj+lfwlIbyLkr+kAj9IW58A/6pE+Vua64NvLZEf29R/TsPXOi7Xx0m+RH465fqMwauV63MV3kq5Phncxk+XmF+Jd1TiH/L410r/+Bf4e/wz5njXFrZ/vgF/U/iluKlfbMe3CH8ON/WLb/FNwju0dJ6/NZ78V/hUpX+kG/5XZfz0dPxiLb4P30/rX15L+07Jv9EBn6zk38jhFaHy/Qfr8cBxuf0P+BuB4zJ/wyvMH9fKh9co5Uvhxynb34D3U7bP4/2V/B/b8GOV+b+JdXp+31qP13k86fGUx9Mez+Bq/mpczV/t2T74l759DFfzn+Nq/mrP/pOe7dO4en08+6/Htfy6ed3pINQ95vEEruXvqPN4yuMZj9fjTbT553hnLf/Wa7rXejzt8RzeSXES7Krr4ybwrlp+eDymxU/iIe3+wV8r8X7dt+Bb8QfwEY5fN8l+fz/AM8L3+8CWZvf1tH+FX42bq1GLdxP+Ll78vr1O/gElf007fFrBjCfa2vpNNZ4W3v8CZ31X/Fan/SHrT9vwyY7L+tP7+E2uy/jIjdTPlfb/VPx+x2V80DT8Xsdl/prn8NGOy/Hruk3EzyjX7xK8h5Y/Cc8W2h8HOtuPLfwX/8GH4dc43ooB986F7XfdzPdV+Om4iV/cE+8j/CE8YuID8LjwPcY645dvsb2WnxIfqsS/zsPPVM7/Mbyflv/pbc/8Slydf46r61d6vM5z/KTn+CnP/tMez3iOn/VsX48vU+IrWrxD/0RhW7z4fAfm+cbPdFw+31m8tZL/YTneFK80LsYfnsGbOC7HH6Jbef8U9h8r9X7Cb8IrjYv9V+N/cVzu/27898C6XL8tmhf1Z5k/Gb/JcTm+Vo8=
*/