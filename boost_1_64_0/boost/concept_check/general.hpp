// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif


// This implementation works on GCC and Comeau, but has actually been
// fairly carefully tuned to work on GCC versions starting with
// gcc-2.95.x.  If you're trying to get an additional compiler to pass
// the tests you might consider breaking out a separate gcc.hpp and
// starting over on the general case.
namespace boost
{
  namespace concept_checking
  {
    template <void(*)()> struct instantiate {};
  }
  
  template <class ModelFn> struct concept_check_;

  template <class Model>
  void concept_check_failed()
  {
      ((Model*)0)->~Model();
  }

  template <class Model>
  struct concept_check
  {
      concept_checking::instantiate<concept_check_failed<Model> > x;
      enum { instantiate = 1 };
  };

# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
  template <class Model>
  void constraint_check_failed()
  {
      ((Model*)0)->constraints();
  }

  template <class Model>
  struct constraint_check
  {
      concept_checking::instantiate<constraint_check_failed<Model> > x;
      enum { instantiate = 1 };
  };
  
  template <class Model>
  struct concept_check_<void(*)(Model)>
    : conditional<
          concept_checking::has_constraints<Model>::value
        , constraint_check<Model>
        , concept_check<Model>
      >::type
  {};
  
# else
  
  template <class Model>
  struct concept_check_<void(*)(Model)>
    : concept_check<Model>
  {};
  
# endif
  
  // Usage, in class or function context:
  //
  //     BOOST_CONCEPT_ASSERT((UnaryFunctionConcept<F,bool,int>));
#  define BOOST_CONCEPT_ASSERT( ModelInParens )                             \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                       \
         ::boost::concept_check_<void(*) ModelInParens>::instantiate        \
  }
}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

/* general.hpp
snpceIyBS5XbVrIghnir01lQ6uwo/ytzCz0YFpRR7TxkpdzAOYzjATu5WY0H6vvSgNBZbHUq2vjtrjCgIanVuY6mHbw90CppwKPvBW7CtMHzi/p/q1Ptmf/yMkOat9hb6cZqQaKMakU/b9BDNS3MBsVr3UzT/2bQM1Wzmu4o0kM0BhRbh7kPYAp8O2jqOmdC/RcVMtjoODe3on6x4f2qK3/RkLdD8siJPZEx2ONGfz5tfGto3tvxPC/OeCrZYeWAaRBbwktwT76667PN5JnOQyd2sixmKyeOERbMT1/ZIsS3Y9+NhB+5TJWsjb6qqvtscyZ2B0+8RMowYRUS4xXc3szDLt9JHS6cTG/v75xbrJy3Htb4aQO/w+XMd/0g8VWuAcfhVwC/9sKvAv/M4Fd5hbNMf0/5VM0vKfiL+ho7YObLTVkahNyPc595y101XO1Xbxzmu4v9yfa+pZn+ynxv1Yr7cInJLyBcWJimkWB5b+74YneyHS4sr2iemYrnySZPwXgSiczNPOQpupdoltYM3GH5yHY1L7hH2edXeuWCt1N25eo+xpcVPRf+vbJAHV7uvS8QyvsYX1Hfvb2BOgPZL0QWB5lUxSgcuS8W+8v9Z4XZf32FycS+OgjIfp+S4e8TnTzYGwV7O+G9Cq+8R3IW0yyTK+cIHx1gS/pHkA/C8g/Serf+Vjh50PFEce9g734tE+dbZ6GfGpwd3Y9MGzw9BhgwD6rRT+7As5Wfwndqb3Cf+QuXBZoWBqxLh+aXjXFky+WAvnK085DewlxHOTkzaKcJrd/rG7TpyxPa8ZX5IW3TZpNW3hTE+dPXSxraP8zn3a4A38vq7ah39nOlfyxzX/tKQ/qRxd6s2nbp9Y7qGPcas3jVIeZBvQU1fgxpL7k60koPWybf9DWHNDV3PqL4MN1HXAdpcI8d5kzlRAcweOa/dYhZUfchV4FqyG/dYEg/vgSpG/fPiU2FOKOxcJx4wwumyqZCf/mdWn/G7yn7S/fwDAyi0J6g30BetP7Vz1/KdoZaxjZ4w8toWlXIjjavxvz3yZdFDJyDodx/baq+z62oGZaaSC0jT//yFa0M8o7f/4XfywMOPIOe2KK/l4stzAPSzyB90BI6g6aAcj94hYpe6hq/n71S9b2sZfz+iKtU38urHFiv3/sfZ9cdXFVTxUMPioqKivipqKjYEQhiZW/v966Aio4aQ/IkkZA88xLENjr2Lo6O+oej6Ngr9q7Yu2LH3hU7thn/cEb33Lt77jn77sPo900C3N/vnO199xz6XW+40bP6O1/P4Mpo7qxONMFfu9XgA5oOzLPL19e4dh5P68znb6AwbEM6fzT2iBtSDOIGhiHVGhdt16yx/MJEgfTyQMzMP3J6oS143deuwbv7VC4XqazcSrqRFoO8tGx/Uz64+fXcrHSqhq9bkm1f8yKLWygS6btOFuu4sSaGwnifmIcXe56X+pHfiOqWpUV6WkZlJJMpiyBOKr9QMkP50DPzgK1U5h5J7kZOkYJEG8A0zjEo955+lERx6Usg8/SjL2nKdz1RqehkWZiBRFfiTTgxCydNwsAPPSXEkk18NByj/EoE0k+8vCoEa/mWHeFZFrdQ5I7nRCDU1SXoEPH+O5U9mGVBEjpOJUxHMTQ3eznjJzJKEvBubjqDofsVb9R8tGmfhWmWlr6wuwnLhuwFK79DL6pUVoCc1X3w/L7E4heneZo4kVNL0fw+afiXefkEQVxkbiSws9ECJ/eaOTnlS1EkMs2ToBK8t+HtbesXmIzMQ6esvFLwHojbrt4NMuzefxVHYSoFdkvd5Sm+wPuCKsx9H7INeyseN0n5pSiqUoJpN3H61KCpb4PHog/Au6I=
*/