///////////////////////////////////////////////////////////////////////////////
/// \file expr.hpp
/// Contains definition of expr\<\> class template.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXPR_HPP_EAN_04_01_2005
#define BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/selection/max.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/traits.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4510) // default constructor could not be generated
# pragma warning(disable : 4512) // assignment operator could not be generated
# pragma warning(disable : 4610) // user defined constructor required
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{

    namespace detail
    {
        struct not_a_valid_type
        {
        private:
            not_a_valid_type()
            {}
        };
        
        template<typename Tag, typename Arg>
        struct address_of_hack
        {
            typedef not_a_valid_type type;
        };

        template<typename Expr>
        struct address_of_hack<proto::tag::address_of, Expr &>
        {
            typedef Expr *type;
        };

        template<typename T, typename Expr, typename Arg0>
        BOOST_FORCEINLINE
        Expr make_terminal(T &t, Expr *, proto::term<Arg0> *)
        {
            Expr that = {t};
            return that;
        }

        template<typename T, typename Expr, typename Arg0, std::size_t N>
        BOOST_FORCEINLINE
        Expr make_terminal(T (&t)[N], Expr *, proto::term<Arg0[N]> *)
        {
            Expr that;
            for(std::size_t i = 0; i < N; ++i)
            {
                that.child0[i] = t[i];
            }
            return that;
        }

        template<typename T, typename Expr, typename Arg0, std::size_t N>
        BOOST_FORCEINLINE
        Expr make_terminal(T const(&t)[N], Expr *, proto::term<Arg0[N]> *)
        {
            Expr that;
            for(std::size_t i = 0; i < N; ++i)
            {
                that.child0[i] = t[i];
            }
            return that;
        }

        // Work-around for:
        // https://connect.microsoft.com/VisualStudio/feedback/details/765449/codegen-stack-corruption-using-runtime-checks-when-aggregate-initializing-struct
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        template<typename T, typename Expr, typename C, typename U>
        BOOST_FORCEINLINE
        Expr make_terminal(T &t, Expr *, proto::term<U C::*> *)
        {
            Expr that;
            that.child0 = t;
            return that;
        }
    #endif

        template<typename T, typename U>
        struct same_cv
        {
            typedef U type;
        };

        template<typename T, typename U>
        struct same_cv<T const, U>
        {
            typedef U const type;
        };
    }

    namespace result_of
    {
        /// \brief A helper metafunction for computing the
        /// return type of \c proto::expr\<\>::operator().
        template<typename Sig, typename This, typename Domain>
        struct funop;

        #include <boost/proto/detail/funop.hpp>
    }

    namespace exprns_
    {
        // This is where the basic_expr specializations are
        // actually defined:
        #include <boost/proto/detail/basic_expr.hpp>

        // This is where the expr specialization are
        // actually defined:
        #include <boost/proto/detail/expr.hpp>
    }

    /// \brief Lets you inherit the interface of an expression
    /// while hiding from Proto the fact that the type is a Proto
    /// expression.
    template<typename Expr>
    struct unexpr
      : Expr
    {
        BOOST_PROTO_UNEXPR()

        BOOST_FORCEINLINE
        explicit unexpr(Expr const &e)
          : Expr(e)
        {}
        
        using Expr::operator =;
    };

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

/* expr.hpp
OygC65BqXLfP+r1x2AjrNoQ/YetIHuDhr/EW5oytooNd/Dc6p7ec4113rPi4phR9DKZCU+CeijO8YAawfH82XRDkJe4/2wN4fw63ia7Pcxc1Xo7RvOyaClug566GV1k/jNv6fl0yxI07ZWhbsLyY01Pk8Lf2QA0aE8Pt8fkCdtccTe5ikStbonrrAik367yOlT1cxzD1FnF4RAGWnRuXb/313EZxFOWt1Pi8hMgK3ea68pDSC1xMxQbXTOu3rYtl16ZReiQu3VKFs4trLGLCZd9QSKZ8P7imkVHcEuu82H56b9jdtvby6UVBUbcBvbwNProzyE15Vw4rI/hWpXlWgMEswrNs67xyCyamtL9JG0HjcJNl33nk62MaPgOyCINCYOn6sb635XCVaGQRdEGTiiWscQQq7mPN2/drrK9Y4/kANXGYVW0n6H1EDevwz3PYRqRNHcdlHYgEwD4Fh79rPJ5IT0DFMscInHnkaHUwXj/LfJ4RZVUXxOTAqniFGjD15pLetbNq2jbgxO/wdC/yz5IqTcj1u8CbCIdjCAL+jmRvN+se2/ejK1+2yAOkFAiSkOOZ3Nn+Of+l1DsD26xOswBbmzlZjex9WerzkbjDfDSgt9CDY4iPESsYPXFb733tMo9qCAt0Bm1AEvTHO+OwCdgVnNyitGqQSUQLFfdcbtr+fWQQ3vWPPXbeXrnw1l0eNCDZv2Hfi5nwefTpXuLx6QQ+bG1Cz3K025ugC56pt2NEzpKbW3AnHY310eDtxa96ZwNWe10mOOchAo1W9OpdNDz62xyW3jyReRdGdWzzekb1IjrZV7UnH/iuldd4/VkwtiqtkxretOAWGnhxzvCcwpdl21aGdZWIxT4x+Er/QBdvpKFx9ZLvFXDQuKhDklsYFdOfS0pf/izDIpF0rbc5vqj+3NWjlQQyLOMcvur7W+uj3a3Bmx+lz9uxSKK0NDl9o4UqUb2K28o+i+FS7jo+du5OnI/FYRQ0lKbZ5DhdSMzZ1Ph8U9Z52hWQjZRay7zW9fMmaAZeFB7t9NvDjdGHWn/OscYqGaSpCHbOc/denoaYv/X5TBcXj7gFa7CwsUxnVXz55rR+3xnh/rvLashtnOXjFAwOpuXHoMkjgtHQGhI5iE0cfg+rS8FOl9l+4zkEnsnhiCEwHM8flvWI1BHLcbyUw633AXxrpuwVrEyr47bPr2VlKnRby6cstu3NDMYGp7Hyd7JyjKwtNzTeo8p7HqBGTcFyHB/gMOyJbRuLW9gYXjW7MCuaMvEixLlpHVgryKWh/fAn2PkirG66WPueeO64OZ3at3njH8DXeocr06SRscAaa+wdb2P8lG478G9vycchKVncDc4b7f0P3qFGnB7bhaTQf9ncEez9JPmgKS+HcZHLqsjgylSTmWFviysVu/u9GGW81eHOz/xMHujL0xLCi0zhk4ek7peubCnCqKz87KG3ssbpPu6YNm15bQKvT7Kkq/JONLu6Nb6gzGOe5iC32lgAD09Fbw92aVVVPZ79o2Vg3Um0091rf8jDU4oOC0kiyekAD8RB7QLCELKv0HZd7vP3Yry8d72DsIFjTiuObhcTGJx+1j14yvc1jasAPhuN0CqZ7oiriaG1fpjeOopEFiaUJjgRIYU4bvqCPf7lhgP93l9k7UBeO1qRhmVVd7LTMTcYIpOT/34naQ9aicS6Qjhcb/Rw1SKpiqRs0kS/GaCQcfkXTRnEI0XWT/Ehvv6aNPQWCoSlo9aQlq/s+x3e+MCfDcdYFsfBMI7oaIMKliHr0yW38+MdojAsyyxLDS7N1o7D1o+P9fN5qP8GZh5kDYRw9c4buqIP0/HhKmW0WT/ccmO8at9n9HCkIpM=
*/