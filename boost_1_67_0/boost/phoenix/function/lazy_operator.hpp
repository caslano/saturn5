////////////////////////////////////////////////////////////////////////////
// lazy operator.hpp
//
// Build lazy operations for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoids in operator.hpp
//
// Implemented so far:
//
// make_pair
// plus minus multiplies divides modulus
// negate equal not_equal greater less
// greater_equal less_equal positive
// logical_and logical_or
// logical_not min max inc dec
//
// These are not from the FC++ operator.hpp but were made for testing purposes.
//
// identity (renamed id)
// sin
//
// These are now being modified to use boost::phoenix::function
// so that they are available for use as arguments.
// Types are being defined in capitals e.g. Id id;
////////////////////////////////////////////////////////////////////////////
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#ifndef BOOST_PHOENIX_FUNCTION_LAZY_OPERATOR
#define BOOST_PHOENIX_FUNCTION_LAZY_OPERATOR

#include <cmath>
#include <cstdlib>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/function.hpp>

namespace boost {

  namespace phoenix {

//////////////////////////////////////////////////////////////////////
// a_unique_type_for_nil
//////////////////////////////////////////////////////////////////////

// This may need to be moved elsewhere to define reuser.
   struct a_unique_type_for_nil {
     bool operator==( a_unique_type_for_nil ) const { return true; }
     bool operator< ( a_unique_type_for_nil ) const { return false; }
     typedef a_unique_type_for_nil value_type;
   };
    // This maybe put into a namespace.
   a_unique_type_for_nil NIL;

//////////////////////////////////////////////////////////////////////
// lazy_exception - renamed from fcpp_exception.
//////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
   struct lazy_exception : public std::exception {
       const char* s;
       lazy_exception( const char* ss ) : s(ss) {}
       const char* what() const throw() { return s; }
   };
#endif

//////////////////////////////////////////////////////////////////////

   // in ref_count.hpp in BoostFC++
   typedef unsigned int RefCountType;

    namespace impl {

      // Implemented early, moved from lazy_signature.hpp
      template <class T>
      struct remove_RC
      {
          typedef typename boost::remove_reference<T>::type TT;
          typedef typename boost::remove_const<TT>::type type;
      };

      struct XId
      {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
           : boost::remove_reference<A0>
        {};

        template <typename A0>
        A0 operator()(A0 const & a0) const
        {
            return a0;
        }

      };


    }

    typedef boost::phoenix::function<impl::XId> Id;
    Id id;

#ifdef BOOST_RESULT_OF_USE_TR1
    // Experiment following examples in
    // phoenix/stl/container/container.hpp

    namespace result_of {

      template <
          typename Arg1
        , typename Arg2
      >
      class make_pair
      {
      public:
        typedef typename impl::remove_RC<Arg1>::type Arg1Type;
        typedef typename impl::remove_RC<Arg2>::type Arg2Type;
        typedef std::pair<Arg1Type,Arg2Type> type;
        typedef std::pair<Arg1Type,Arg2Type> result_type;
      };
    }
#endif

  namespace impl
  {

    struct XMake_pair {


#ifdef BOOST_RESULT_OF_USE_TR1
       template <typename Sig>
       struct result;
       // This fails with -O2 unless refs are removed from A1 and A2.
       template <typename This, typename A0, typename A1>
       struct result<This(A0, A1)>
       {
         typedef typename result_of::make_pair<A0,A1>::type type;
       };
#else
       template <typename Sig>
       struct result;

       template <typename This, typename A0, typename A1>
       struct result<This(A0, A1)>
         : boost::remove_reference<std::pair<A0, A1> >
       {};
      
#endif


       template <typename A0, typename A1>
#ifdef BOOST_RESULT_OF_USE_TR1
       typename result<XMake_pair(A0,A1)>::type
#else
       std::pair<A0, A1>
#endif
       operator()(A0 const & a0, A1 const & a1) const
       {
          return std::make_pair(a0,a1);
       }

    };
  }

  typedef boost::phoenix::function<impl::XMake_pair> Make_pair;
  Make_pair make_pair;

  namespace impl
  {

    // For now I will leave the return type deduction as it is.
    // I want to look at bringing in the sort of type deduction for
    // mixed types which I have in FC++.
    // Also I could look at the case where one of the arguments is
    // another functor or a Phoenix placeholder.
    struct XPlus
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
             : boost::remove_reference<A0>
        {};

        template <typename This, typename A0, typename A1, typename A2>
        struct result<This(A0, A1, A2)>
             : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
          //A0 res = a0 + a1;
          //return res;
          return a0 + a1;
        }

        template <typename A0, typename A1, typename A2>
        A0 operator()(A0 const & a0, A1 const & a1, A2 const & a2) const
        {
            return a0 + a1 + a2;
        }
    };

    struct XMinus
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
           : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 - a1;
        }

    };

    struct XMultiplies
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
           : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 * a1;
        }

    };

    struct XDivides
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
           : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 / a1;
        }

    };

    struct XModulus
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
          : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 % a1;
        }

    };

    struct XNegate
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
           : boost::remove_reference<A0>
        {};

        template <typename A0>
        A0 operator()(A0 const & a0) const
        {
            return -a0;
        }
    };

    struct XEqual
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 == a1;
        }
    };

    struct XNot_equal
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 != a1;
        }
    };

    struct XGreater
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 > a1;
        }
    };

    struct XLess
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 < a1;
        }
    };

    struct XGreater_equal
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 >= a1;
        }
    };

    struct XLess_equal
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 <= a1;
        }
    };

    struct XPositive
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
        {
            typedef bool type;
        };

        template <typename A0>
        bool operator()(A0 const & a0) const
        {
          return a0 >= A0(0);
        }
    };

    struct XLogical_and
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 && a1;
        }
    };

    struct XLogical_or
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
        {
            typedef bool type;
        };

        template <typename A0, typename A1>
        bool operator()(A0 const & a0, A1 const & a1) const
        {
            return a0 || a1;
        }
    };

    struct XLogical_not
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
        {
             typedef bool type;
        };

        template <typename A0>
        bool operator()(A0 const & a0) const
        {
            return !a0;
        }
    };

    struct XMin
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
          : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
           if ( a0 < a1 ) return a0; else return a1;
        }

    };

    struct XMax
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0, typename A1>
        struct result<This(A0, A1)>
          : boost::remove_reference<A0>
        {};

        template <typename A0, typename A1>
        A0 operator()(A0 const & a0, A1 const & a1) const
        {
           if ( a0 < a1 ) return a1; else return a0;
        }

    };

    struct XInc
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
           : boost::remove_reference<A0>
        {};

        template <typename A0>
        A0 operator()(A0 const & a0) const
        {
            return a0 + 1;
        }

    };

    struct XDec
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
           : boost::remove_reference<A0>
        {};

        template <typename A0>
        A0 operator()(A0 const & a0) const
        {
            return a0 - 1;
        }

    };

    struct XSin
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0>
        struct result<This(A0)>
           : boost::remove_reference<A0>
        {};

        template <typename A0>
        A0 operator()(A0 const & a0) const
        {
          return std::sin(a0);
        }

    };

    // Example of templated struct.
    // How do I make it callable?
    template <typename Result>
    struct what {

      typedef Result result_type;

      Result operator()(Result const & r) const
      {
        return r;
      }
      // what is not complete - error.
      //static boost::function1<Result,Result> res = what<Result>();
    };

    template <typename Result>
    struct what0 {

      typedef Result result_type;

      Result operator()() const
      {
        return Result(100);
      }

    };


      template <class Result, class F>
      class MonomorphicWrapper0 /* : public c_fun_type<Res> */
      {
          F f;
      public:
          typedef Result result_type;
          MonomorphicWrapper0( const F& g ) : f(g) {}
             Result operator()() const {
             return f();
          }
      };

  }
    /////////////////////////////////////////////////////////
    // Look at this. How to use Phoenix with a templated
    // struct. First adapt with boost::function and then
    // convert that to Phoenix!!
    // I have not found out how to do it directly.
    /////////////////////////////////////////////////////////
boost::function1<int, int > what_int = impl::what<int>();
typedef boost::function1<int,int> fun1_int_int;
typedef boost::function0<int> fun0_int;
boost::function0<int> what0_int = impl::what0<int>();
BOOST_PHOENIX_ADAPT_FUNCTION(int,what,what_int,1)
BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(int,what0,what0_int)
// And this shows how to make them into argument callable functions.
typedef boost::phoenix::function<fun1_int_int> What_arg;
typedef boost::phoenix::function<fun0_int> What0_arg;
What_arg what_arg(what_int);
What0_arg what0_arg(what0_int);


// To use these as arguments they have to be defined like this.
    typedef boost::phoenix::function<impl::XPlus> Plus;
    typedef boost::phoenix::function<impl::XMinus> Minus;
    typedef boost::phoenix::function<impl::XMultiplies> Multiplies;
    typedef boost::phoenix::function<impl::XDivides>   Divides;
    typedef boost::phoenix::function<impl::XModulus>   Modulus;
    typedef boost::phoenix::function<impl::XNegate>    Negate;
    typedef boost::phoenix::function<impl::XEqual>     Equal;
    typedef boost::phoenix::function<impl::XNot_equal> Not_equal;
    typedef boost::phoenix::function<impl::XGreater>   Greater;
    typedef boost::phoenix::function<impl::XLess>      Less;
    typedef boost::phoenix::function<impl::XGreater_equal> Greater_equal;
    typedef boost::phoenix::function<impl::XLess_equal>    Less_equal;
    typedef boost::phoenix::function<impl::XPositive>    Positive;
    typedef boost::phoenix::function<impl::XLogical_and> Logical_and;
    typedef boost::phoenix::function<impl::XLogical_or>  Logical_or;
    typedef boost::phoenix::function<impl::XLogical_not> Logical_not;
    typedef boost::phoenix::function<impl::XMax> Max;
    typedef boost::phoenix::function<impl::XMin> Min;
    typedef boost::phoenix::function<impl::XInc> Inc;
    typedef boost::phoenix::function<impl::XDec> Dec;
    typedef boost::phoenix::function<impl::XSin> Sin;
    Plus plus;
    Minus minus;
    Multiplies multiplies;
    Divides divides;
    Modulus modulus;
    Negate  negate;
    Equal   equal;
    Not_equal not_equal;
    Greater greater;
    Less    less;
    Greater_equal greater_equal;
    Less_equal    less_equal;
    Positive      positive;
    Logical_and   logical_and;
    Logical_or    logical_or;
    Logical_not   logical_not;
    Max max;
    Min min;
    Inc inc;
    Dec dec;
    Sin sin;
}

}


#endif

/* lazy_operator.hpp
+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
*/