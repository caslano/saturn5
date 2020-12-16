///////////////////////////////////////////////////////////////////////////////
/// \file fold_tree.hpp
/// Contains definition of the fold_tree<> and reverse_fold_tree<> transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007
#define BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007

#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/impl.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Tag>
        struct has_tag
        {
            template<typename Expr, typename State, typename Data, typename EnableIf = Tag>
            struct impl
            {
                typedef mpl::false_ result_type;
            };

            template<typename Expr, typename State, typename Data>
            struct impl<Expr, State, Data, typename Expr::proto_tag>
            {
                typedef mpl::true_ result_type;
            };

            template<typename Expr, typename State, typename Data>
            struct impl<Expr &, State, Data, typename Expr::proto_tag>
            {
                typedef mpl::true_ result_type;
            };
        };

        template<typename Tag, typename Fun>
        struct fold_tree_
          : if_<has_tag<Tag>, fold<_, _state, fold_tree_<Tag, Fun> >, Fun>
        {};

        template<typename Tag, typename Fun>
        struct reverse_fold_tree_
          : if_<has_tag<Tag>, reverse_fold<_, _state, reverse_fold_tree_<Tag, Fun> >, Fun>
        {};
    }

    /// \brief A PrimitiveTransform that recursively applies the
    /// <tt>fold\<\></tt> transform to sub-trees that all share a common
    /// tag type.
    ///
    /// <tt>fold_tree\<\></tt> is useful for flattening trees into lists;
    /// for example, you might use <tt>fold_tree\<\></tt> to flatten an
    /// expression tree like <tt>a | b | c</tt> into a Fusion list like
    /// <tt>cons(c, cons(b, cons(a)))</tt>.
    ///
    /// <tt>fold_tree\<\></tt> is easily understood in terms of a
    /// <tt>recurse_if_\<\></tt> helper, defined as follows:
    ///
    /// \code
    /// template<typename Tag, typename Fun>
    /// struct recurse_if_
    ///   : if_<
    ///         // If the current node has type "Tag" ...
    ///         is_same<tag_of<_>, Tag>()
    ///         // ... recurse, otherwise ...
    ///       , fold<_, _state, recurse_if_<Tag, Fun> >
    ///         // ... apply the Fun transform.
    ///       , Fun
    ///     >
    /// {};
    /// \endcode
    ///
    /// With <tt>recurse_if_\<\></tt> as defined above,
    /// <tt>fold_tree\<Sequence, State0, Fun\>()(e, s, d)</tt> is
    /// equivalent to
    /// <tt>fold<Sequence, State0, recurse_if_<Expr::proto_tag, Fun> >()(e, s, d).</tt>
    /// It has the effect of folding a tree front-to-back, recursing into
    /// child nodes that share a tag type with the parent node.
    template<typename Sequence, typename State0, typename Fun>
    struct fold_tree
      : transform<fold_tree<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : fold<
                Sequence
              , State0
              , detail::fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : fold<
                Sequence
              , State0
              , detail::fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr &, State, Data>
        {};
    };

    /// \brief A PrimitiveTransform that recursively applies the
    /// <tt>reverse_fold\<\></tt> transform to sub-trees that all share
    /// a common tag type.
    ///
    /// <tt>reverse_fold_tree\<\></tt> is useful for flattening trees into
    /// lists; for example, you might use <tt>reverse_fold_tree\<\></tt> to
    /// flatten an expression tree like <tt>a | b | c</tt> into a Fusion list
    /// like <tt>cons(a, cons(b, cons(c)))</tt>.
    ///
    /// <tt>reverse_fold_tree\<\></tt> is easily understood in terms of a
    /// <tt>recurse_if_\<\></tt> helper, defined as follows:
    ///
    /// \code
    /// template<typename Tag, typename Fun>
    /// struct recurse_if_
    ///   : if_<
    ///         // If the current node has type "Tag" ...
    ///         is_same<tag_of<_>, Tag>()
    ///         // ... recurse, otherwise ...
    ///       , reverse_fold<_, _state, recurse_if_<Tag, Fun> >
    ///         // ... apply the Fun transform.
    ///       , Fun
    ///     >
    /// {};
    /// \endcode
    ///
    /// With <tt>recurse_if_\<\></tt> as defined above,
    /// <tt>reverse_fold_tree\<Sequence, State0, Fun\>()(e, s, d)</tt> is
    /// equivalent to
    /// <tt>reverse_fold<Sequence, State0, recurse_if_<Expr::proto_tag, Fun> >()(e, s, d).</tt>
    /// It has the effect of folding a tree back-to-front, recursing into
    /// child nodes that share a tag type with the parent node.
    template<typename Sequence, typename State0, typename Fun>
    struct reverse_fold_tree
      : transform<reverse_fold_tree<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : reverse_fold<
                Sequence
              , State0
              , detail::reverse_fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : reverse_fold<
                Sequence
              , State0
              , detail::reverse_fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr &, State, Data>
        {};
    };

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<reverse_fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};

}}

#endif

/* fold_tree.hpp
8z+4Or8s5y934U8qLtc3fI1vUFzev/Ud/ojisn+0McNjlCnz93J9ykv4S9SvbMWnLXPmT1/GXxS+ArfmF17Bnxe+Hbfin9jWY3QXPu63SvvH5MqcBNc3s8305eGHi+uPHyzldzN9p+Hdhfc8y+kfFeIdhIdxK30345S/PXwLbr1b0dljdMLsLUT7fAXeVnE5v3UlfrDicn7rKryN4nJ+6wa8mepyfovJqxu8jfOvnTW/hf8eT1f84O7O/P1G/FzhJ+FW+7EJP0f4jbjVfjyF1you1z/mddO3f4X46ATzX/1MvwBPx9X1n18scerfY/irxp4+eKkT2hoKx2G669N4vTf5+fczPKfx/Jt9/v0cHyL8D7iVf1/gg4V/ilv59yU+UPjUJcrxzfQY3VKTp289/hb990GKX1XspO8J/A3hb+JW+jbgrwnvF3DS9yd8s/DluD1+7usxMtT6K+fP8ZTG69/s49eMmz+3GIqL+z+b428qLu//bIG/rrgc32zDv9SM77fjnysux7deGp8/Ky7nR1LwFxSX91cMx1drrg/W43Wa8ddWvAwfpri/k3N838VLhB8zwzm+7+F+4ctx6/i+j/uEf4Hb45sBnN819WMJnoJ3UHxHB2V+GPcI73WIMj+M/+JRXNw/sAz/SXF5/0Adixsu0ax/uwlfrrg8f2/CyxSX6xuzqbwfaMLPwd/ThD8Nf0JxOf83HX9ccTn/dwr+qOJy/i8jy2M8oKz/kufPbPxcPC1DKd/VzvlzBL5E+MO4dX7KxcPCWy9yYluB9xIexe3ynU3/RHP/9WZ8neb+61fxBzX3367IMfuXSa6P3YvfbcjrY07/6gH8NsXl9dkH8VsUl9dnQ0M99vg/O1H9wEN4X8XV+ZOleFBxOX9yFl6uuJw/WYbPV1zOnxhH0X9t1zh/epvpOwQf0Yq9Uc6fuxY546NMfJDwnMVO+nrhA4Sfi1vp6433F/4pbtffCR7jIeX+CHn98A18Cd5B8ZlDnNLwGV4s/J2Isv4bP1n4wKhz/FIneoxJwi/D7fEb+JyhpE+uz8efUV2uz8efUl2uz8c3Ki7779ksTng6wf0Zp1v9Y/wKnGbM9pQqxv1m/Gfg5wsfiw8x478EP1X4lbh1/C7FZwr/EbfL11TSp9Q/2f70xq/k52mKP7WQ+oHG9w+/QLgn7IRWj6vXJ+T6lM14reJyfcqr+BLF5fqU1/Aa4Zy/7fUDW/CI5v7IwpNoqTT9yxA+2pN8fLkQP96T/PrY67h6/4Zcn/0G/rbwsyqV8R+F/3Pd+n/8Sc31uTV5HmOC4vL+1HX4aM32xjTGL7r7g/GDvcnv/8jEd4v7u9+vtLbGT/EYXTT5n4vr7g/Nw5tpvBCfobn+vBGPavYvd4Z++zr8II+ysby/Hf+Fnx0Uf32gk9r1+JfC2w9Sxj8zPUaV7v5cPKK5P+MJfIbisv+yCT9JeDel/GXP8hizU5I/3yQP/wc/+6c63j3knP+n4R8LPyPkhPYVi7/7sTOqP4hb8f8L7ym820JlfD+b8bPm+D2E1ygmxwfr8EWKyetbX+JdVJTt+xzO/5r4T8RPUUwen9/iXRWT/dc6XDf+XoMfq6k/O/Xbxx8O8W5K8vk9Dx5UXN7f78XnKy7zbxsPD1mqu78OP1MzP9e6wGNM1dy/VIjr9q8W/zHB9d3u5vsr8Tfw0xQfXuGcf67F/yq8Crf6T9fhrwh/DrfOv9fjLyku179W++LpT+q1+AIj+fzVZXi+5vr2Tjxbc39KJouTbtRc3xyIr9Rc3xyEr9Bc3xyML9dc3xyGn6O5vrkR15RvAqP+WBmX4P7yjvgfUpy8lfdXd8KvUlzeXx3Ejxf+ermT25k=
*/