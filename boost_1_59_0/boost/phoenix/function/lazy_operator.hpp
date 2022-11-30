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
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
*/