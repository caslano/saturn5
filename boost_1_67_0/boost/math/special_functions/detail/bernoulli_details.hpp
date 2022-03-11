///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BERNOULLI_DETAIL_HPP
#define BOOST_MATH_BERNOULLI_DETAIL_HPP

#include <boost/config.hpp>
#include <boost/detail/lightweight_mutex.hpp>
#include <boost/math/tools/atomic.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/math/tools/toms748_solve.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#include <vector>

namespace boost{ namespace math{ namespace detail{
//
// Asymptotic expansion for B2n due to
// Luschny LogB3 formula (http://www.luschny.de/math/primes/bernincl.html)
//
template <class T, class Policy>
T b2n_asymptotic(int n)
{
   BOOST_MATH_STD_USING
   const T nx = static_cast<T>(n);
   const T nx2(nx * nx);

   const T approximate_log_of_bernoulli_bn = 
        ((boost::math::constants::half<T>() + nx) * log(nx))
        + ((boost::math::constants::half<T>() - nx) * log(boost::math::constants::pi<T>()))
        + (((T(3) / 2) - nx) * boost::math::constants::ln_two<T>())
        + ((nx * (T(2) - (nx2 * 7) * (1 + ((nx2 * 30) * ((nx2 * 12) - 1))))) / (((nx2 * nx2) * nx2) * 2520));
   return ((n / 2) & 1 ? 1 : -1) * (approximate_log_of_bernoulli_bn > tools::log_max_value<T>() 
      ? policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, nx, Policy())
      : static_cast<T>(exp(approximate_log_of_bernoulli_bn)));
}

template <class T, class Policy>
T t2n_asymptotic(int n)
{
   BOOST_MATH_STD_USING
   // Just get B2n and convert to a Tangent number:
   T t2n = fabs(b2n_asymptotic<T, Policy>(2 * n)) / (2 * n);
   T p2 = ldexp(T(1), n);
   if(tools::max_value<T>() / p2 < t2n)
      return policies::raise_overflow_error<T>("boost::math::tangent_t2n<%1%>(std::size_t)", 0, T(n), Policy());
   t2n *= p2;
   p2 -= 1;
   if(tools::max_value<T>() / p2 < t2n)
      return policies::raise_overflow_error<T>("boost::math::tangent_t2n<%1%>(std::size_t)", 0, Policy());
   t2n *= p2;
   return t2n;
}
//
// We need to know the approximate value of /n/ which will
// cause bernoulli_b2n<T>(n) to return infinity - this allows
// us to elude a great deal of runtime checking for values below
// n, and only perform the full overflow checks when we know that we're
// getting close to the point where our calculations will overflow.
// We use Luschny's LogB3 formula (http://www.luschny.de/math/primes/bernincl.html) 
// to find the limit, and since we're dealing with the log of the Bernoulli numbers
// we need only perform the calculation at double precision and not with T
// (which may be a multiprecision type).  The limit returned is within 1 of the true
// limit for all the types tested.  Note that although the code below is basically
// the same as b2n_asymptotic above, it has been recast as a continuous real-valued 
// function as this makes the root finding go smoother/faster.  It also omits the
// sign of the Bernoulli number.
//
struct max_bernoulli_root_functor
{
   max_bernoulli_root_functor(ulong_long_type t) : target(static_cast<double>(t)) {}
   double operator()(double n)
   {
      BOOST_MATH_STD_USING

      // Luschny LogB3(n) formula.

      const double nx2(n * n);

      const double approximate_log_of_bernoulli_bn
         =   ((boost::math::constants::half<double>() + n) * log(n))
           + ((boost::math::constants::half<double>() - n) * log(boost::math::constants::pi<double>()))
           + (((double(3) / 2) - n) * boost::math::constants::ln_two<double>())
           + ((n * (2 - (nx2 * 7) * (1 + ((nx2 * 30) * ((nx2 * 12) - 1))))) / (((nx2 * nx2) * nx2) * 2520));

      return approximate_log_of_bernoulli_bn - target;
   }
private:
   double target;
};

template <class T, class Policy>
inline std::size_t find_bernoulli_overflow_limit(const boost::false_type&)
{
   // Set a limit on how large the result can ever be:
   static const double max_result = static_cast<double>((std::numeric_limits<std::size_t>::max)() - 1000u);

   ulong_long_type t = lltrunc(boost::math::tools::log_max_value<T>());
   max_bernoulli_root_functor fun(t);
   boost::math::tools::equal_floor tol;
   boost::uintmax_t max_iter = boost::math::policies::get_max_root_iterations<Policy>();
   double result = boost::math::tools::toms748_solve(fun, sqrt(double(t)), double(t), tol, max_iter).first / 2;
   if (result > max_result)
      result = max_result;
   
   return static_cast<std::size_t>(result);
}

template <class T, class Policy>
inline std::size_t find_bernoulli_overflow_limit(const boost::true_type&)
{
   return max_bernoulli_index<bernoulli_imp_variant<T>::value>::value;
}

template <class T, class Policy>
std::size_t b2n_overflow_limit()
{
   // This routine is called at program startup if it's called at all:
   // that guarantees safe initialization of the static variable.
   typedef boost::integral_constant<bool, (bernoulli_imp_variant<T>::value >= 1) && (bernoulli_imp_variant<T>::value <= 3)> tag_type;
   static const std::size_t lim = find_bernoulli_overflow_limit<T, Policy>(tag_type());
   return lim;
}

//
// The tangent numbers grow larger much more rapidly than the Bernoulli numbers do....
// so to compute the Bernoulli numbers from the tangent numbers, we need to avoid spurious
// overflow in the calculation, we can do this by scaling all the tangent number by some scale factor:
//
template <class T>
inline typename enable_if_c<std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::radix == 2), T>::type tangent_scale_factor()
{
   BOOST_MATH_STD_USING
   return ldexp(T(1), std::numeric_limits<T>::min_exponent + 5);
}
template <class T>
inline typename disable_if_c<std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::radix == 2), T>::type tangent_scale_factor()
{
   return tools::min_value<T>() * 16;
}
//
// Initializer: ensure all our constants are initialized prior to the first call of main:
//
template <class T, class Policy>
struct bernoulli_initializer
{
   struct init
   {
      init()
      {
         //
         // We call twice, once to initialize our static table, and once to
         // initialize our dymanic table:
         //
         boost::math::bernoulli_b2n<T>(2, Policy());
#ifndef BOOST_NO_EXCEPTIONS
         try{
#endif
            boost::math::bernoulli_b2n<T>(max_bernoulli_b2n<T>::value + 1, Policy());
#ifndef BOOST_NO_EXCEPTIONS
         } catch(const std::overflow_error&){}
#endif
         boost::math::tangent_t2n<T>(2, Policy());
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy>
const typename bernoulli_initializer<T, Policy>::init bernoulli_initializer<T, Policy>::initializer;

//
// We need something to act as a cache for our calculated Bernoulli numbers.  In order to
// ensure both fast access and thread safety, we need a stable table which may be extended
// in size, but which never reallocates: that way values already calculated may be accessed
// concurrently with another thread extending the table with new values.
//
// Very very simple vector class that will never allocate more than once, we could use
// boost::container::static_vector here, but that allocates on the stack, which may well
// cause issues for the amount of memory we want in the extreme case...
//
template <class T>
struct fixed_vector : private std::allocator<T>
{
   typedef unsigned size_type;
   typedef T* iterator;
   typedef const T* const_iterator;
   fixed_vector() : m_used(0)
   { 
      std::size_t overflow_limit = 5 + b2n_overflow_limit<T, policies::policy<> >();
      m_capacity = static_cast<unsigned>((std::min)(overflow_limit, static_cast<std::size_t>(100000u)));
      m_data = this->allocate(m_capacity); 
   }
   ~fixed_vector()
   {
#ifdef BOOST_NO_CXX11_ALLOCATOR
      for(unsigned i = 0; i < m_used; ++i)
         this->destroy(&m_data[i]);
      this->deallocate(m_data, m_capacity);
#else
      typedef std::allocator<T> allocator_type;
      typedef std::allocator_traits<allocator_type> allocator_traits; 
      allocator_type& alloc = *this; 
      for(unsigned i = 0; i < m_used; ++i)
         allocator_traits::destroy(alloc, &m_data[i]);
      allocator_traits::deallocate(alloc, m_data, m_capacity);
#endif
   }
   T& operator[](unsigned n) { BOOST_ASSERT(n < m_used); return m_data[n]; }
   const T& operator[](unsigned n)const { BOOST_ASSERT(n < m_used); return m_data[n]; }
   unsigned size()const { return m_used; }
   unsigned size() { return m_used; }
   void resize(unsigned n, const T& val)
   {
      if(n > m_capacity)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error("Exhausted storage for Bernoulli numbers."));
      }
      for(unsigned i = m_used; i < n; ++i)
         new (m_data + i) T(val);
      m_used = n;
   }
   void resize(unsigned n) { resize(n, T()); }
   T* begin() { return m_data; }
   T* end() { return m_data + m_used; }
   T* begin()const { return m_data; }
   T* end()const { return m_data + m_used; }
   unsigned capacity()const { return m_capacity; }
   void clear() { m_used = 0; }
private:
   T* m_data;
   unsigned m_used, m_capacity;
};

template <class T, class Policy>
class bernoulli_numbers_cache
{
public:
   bernoulli_numbers_cache() : m_overflow_limit((std::numeric_limits<std::size_t>::max)())
#if defined(BOOST_HAS_THREADS) && !defined(BOOST_MATH_NO_ATOMIC_INT)
      , m_counter(0)
#endif
      , m_current_precision(boost::math::tools::digits<T>())
   {}

   typedef fixed_vector<T> container_type;

   void tangent(std::size_t m)
   {
      static const std::size_t min_overflow_index = b2n_overflow_limit<T, Policy>() - 1;
      tn.resize(static_cast<typename container_type::size_type>(m), T(0U));

      BOOST_MATH_INSTRUMENT_VARIABLE(min_overflow_index);

      std::size_t prev_size = m_intermediates.size();
      m_intermediates.resize(m, T(0U));

      if(prev_size == 0)
      {
         m_intermediates[1] = tangent_scale_factor<T>() /*T(1U)*/;
         tn[0U] = T(0U);
         tn[1U] = tangent_scale_factor<T>()/* T(1U)*/;
         BOOST_MATH_INSTRUMENT_VARIABLE(tn[0]);
         BOOST_MATH_INSTRUMENT_VARIABLE(tn[1]);
      }

      for(std::size_t i = std::max<size_t>(2, prev_size); i < m; i++)
      {
         bool overflow_check = false;
         if(i >= min_overflow_index && (boost::math::tools::max_value<T>() / (i-1) < m_intermediates[1]) )
         {
            std::fill(tn.begin() + i, tn.end(), boost::math::tools::max_value<T>());
            break;
         }
         m_intermediates[1] = m_intermediates[1] * (i-1);
         for(std::size_t j = 2; j <= i; j++)
         {
            overflow_check =
                  (i >= min_overflow_index) && (
                  (boost::math::tools::max_value<T>() / (i - j) < m_intermediates[j])
                  || (boost::math::tools::max_value<T>() / (i - j + 2) < m_intermediates[j-1])
                  || (boost::math::tools::max_value<T>() - m_intermediates[j] * (i - j) < m_intermediates[j-1] * (i - j + 2))
                  || ((boost::math::isinf)(m_intermediates[j]))
                );

            if(overflow_check)
            {
               std::fill(tn.begin() + i, tn.end(), boost::math::tools::max_value<T>());
               break;
            }
            m_intermediates[j] = m_intermediates[j] * (i - j) + m_intermediates[j-1] * (i - j + 2);
         }
         if(overflow_check)
            break; // already filled the tn...
         tn[static_cast<typename container_type::size_type>(i)] = m_intermediates[i];
         BOOST_MATH_INSTRUMENT_VARIABLE(i);
         BOOST_MATH_INSTRUMENT_VARIABLE(tn[static_cast<typename container_type::size_type>(i)]);
      }
   }

   void tangent_numbers_series(const std::size_t m)
   {
      BOOST_MATH_STD_USING
      static const std::size_t min_overflow_index = b2n_overflow_limit<T, Policy>() - 1;

      typename container_type::size_type old_size = bn.size();

      tangent(m);
      bn.resize(static_cast<typename container_type::size_type>(m));

      if(!old_size)
      {
         bn[0] = 1;
         old_size = 1;
      }

      T power_two(ldexp(T(1), static_cast<int>(2 * old_size)));

      for(std::size_t i = old_size; i < m; i++)
      {
         T b(static_cast<T>(i * 2));
         //
         // Not only do we need to take care to avoid spurious over/under flow in
         // the calculation, but we also need to avoid overflow altogether in case
         // we're calculating with a type where "bad things" happen in that case:
         //
         b  = b / (power_two * tangent_scale_factor<T>());
         b /= (power_two - 1);
         bool overflow_check = (i >= min_overflow_index) && (tools::max_value<T>() / tn[static_cast<typename container_type::size_type>(i)] < b);
         if(overflow_check)
         {
            m_overflow_limit = i;
            while(i < m)
            {
               b = std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : tools::max_value<T>();
               bn[static_cast<typename container_type::size_type>(i)] = ((i % 2U) ? b : T(-b));
               ++i;
            }
            break;
         }
         else
         {
            b *= tn[static_cast<typename container_type::size_type>(i)];
         }

         power_two = ldexp(power_two, 2);

         const bool b_neg = i % 2 == 0;

         bn[static_cast<typename container_type::size_type>(i)] = ((!b_neg) ? b : T(-b));
      }
   }

   template <class OutputIterator>
   OutputIterator copy_bernoulli_numbers(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol)
   {
      //
      // There are basically 3 thread safety options:
      //
      // 1) There are no threads (BOOST_HAS_THREADS is not defined).
      // 2) There are threads, but we do not have a true atomic integer type, 
      //    in this case we just use a mutex to guard against race conditions.
      // 3) There are threads, and we have an atomic integer: in this case we can
      //    use the double-checked locking pattern to avoid thread synchronisation
      //    when accessing values already in the cache.
      //
      // First off handle the common case for overflow and/or asymptotic expansion:
      //
      if(start + n > bn.capacity())
      {
         if(start < bn.capacity())
         {
            out = copy_bernoulli_numbers(out, start, bn.capacity() - start, pol);
            n -= bn.capacity() - start;
            start = static_cast<std::size_t>(bn.capacity());
         }
         if(start < b2n_overflow_limit<T, Policy>() + 2u)
         {
            for(; n; ++start, --n)
            {
               *out = b2n_asymptotic<T, Policy>(static_cast<typename container_type::size_type>(start * 2U));
               ++out;
            }
         }
         for(; n; ++start, --n)
         {
            *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(start), pol);
            ++out;
         }
         return out;
      }
   #if !defined(BOOST_HAS_THREADS)
      //
      // Single threaded code, very simple:
      //
      if(m_current_precision < boost::math::tools::digits<T>())
      {
         bn.clear();
         tn.clear();
         m_intermediates.clear();
         m_current_precision = boost::math::tools::digits<T>();
      }
      if(start + n >= bn.size())
      {
         std::size_t new_size = (std::min)((std::max)((std::max)(std::size_t(start + n), std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
         tangent_numbers_series(new_size);
      }

      for(std::size_t i = (std::max)(std::size_t(max_bernoulli_b2n<T>::value + 1), start); i < start + n; ++i)
      {
         *out = (i >= m_overflow_limit) ? policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol) : bn[i];
         ++out;
      }
   #elif defined(BOOST_MATH_NO_ATOMIC_INT)
      //
      // We need to grab a mutex every time we get here, for both readers and writers:
      //
      boost::detail::lightweight_mutex::scoped_lock l(m_mutex);
      if(m_current_precision < boost::math::tools::digits<T>())
      {
         bn.clear();
         tn.clear();
         m_intermediates.clear();
         m_current_precision = boost::math::tools::digits<T>();
      }
      if(start + n >= bn.size())
      {
         std::size_t new_size = (std::min)((std::max)((std::max)(std::size_t(start + n), std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
         tangent_numbers_series(new_size);
      }

      for(std::size_t i = (std::max)(std::size_t(max_bernoulli_b2n<T>::value + 1), start); i < start + n; ++i)
      {
         *out = (i >= m_overflow_limit) ? policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol) : bn[i];
         ++out;
      }

   #else
      //
      // Double-checked locking pattern, lets us access cached already cached values
      // without locking:
      //
      // Get the counter and see if we need to calculate more constants:
      //
      if((static_cast<std::size_t>(m_counter.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < start + n)
         || (static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>()))
      {
         boost::detail::lightweight_mutex::scoped_lock l(m_mutex);

         if((static_cast<std::size_t>(m_counter.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < start + n)
            || (static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>()))
         {
            if(static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>())
            {
               bn.clear();
               tn.clear();
               m_intermediates.clear();
               m_counter.store(0, BOOST_MATH_ATOMIC_NS::memory_order_release);
               m_current_precision = boost::math::tools::digits<T>();
            }
            if(start + n >= bn.size())
            {
               std::size_t new_size = (std::min)((std::max)((std::max)(std::size_t(start + n), std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
               tangent_numbers_series(new_size);
            }
            m_counter.store(static_cast<atomic_integer_type>(bn.size()), BOOST_MATH_ATOMIC_NS::memory_order_release);
         }
      }

      for(std::size_t i = (std::max)(static_cast<std::size_t>(max_bernoulli_b2n<T>::value + 1), start); i < start + n; ++i)
      {
         *out = (i >= m_overflow_limit) ? policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol) : bn[static_cast<typename container_type::size_type>(i)];
         ++out;
      }

   #endif
      return out;
   }

   template <class OutputIterator>
   OutputIterator copy_tangent_numbers(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol)
   {
      //
      // There are basically 3 thread safety options:
      //
      // 1) There are no threads (BOOST_HAS_THREADS is not defined).
      // 2) There are threads, but we do not have a true atomic integer type, 
      //    in this case we just use a mutex to guard against race conditions.
      // 3) There are threads, and we have an atomic integer: in this case we can
      //    use the double-checked locking pattern to avoid thread synchronisation
      //    when accessing values already in the cache.
      //
      //
      // First off handle the common case for overflow and/or asymptotic expansion:
      //
      if(start + n > bn.capacity())
      {
         if(start < bn.capacity())
         {
            out = copy_tangent_numbers(out, start, bn.capacity() - start, pol);
            n -= bn.capacity() - start;
            start = static_cast<std::size_t>(bn.capacity());
         }
         if(start < b2n_overflow_limit<T, Policy>() + 2u)
         {
            for(; n; ++start, --n)
            {
               *out = t2n_asymptotic<T, Policy>(static_cast<typename container_type::size_type>(start));
               ++out;
            }
         }
         for(; n; ++start, --n)
         {
            *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(start), pol);
            ++out;
         }
         return out;
      }
   #if !defined(BOOST_HAS_THREADS)
      //
      // Single threaded code, very simple:
      //
      if(m_current_precision < boost::math::tools::digits<T>())
      {
         bn.clear();
         tn.clear();
         m_intermediates.clear();
         m_current_precision = boost::math::tools::digits<T>();
      }
      if(start + n >= bn.size())
      {
         std::size_t new_size = (std::min)((std::max)((std::max)(start + n, std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
         tangent_numbers_series(new_size);
      }

      for(std::size_t i = start; i < start + n; ++i)
      {
         if(i >= m_overflow_limit)
            *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
         else
         {
            if(tools::max_value<T>() * tangent_scale_factor<T>() < tn[static_cast<typename container_type::size_type>(i)])
               *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
            else
               *out = tn[static_cast<typename container_type::size_type>(i)] / tangent_scale_factor<T>();
         }
         ++out;
      }
   #elif defined(BOOST_MATH_NO_ATOMIC_INT)
      //
      // We need to grab a mutex every time we get here, for both readers and writers:
      //
      boost::detail::lightweight_mutex::scoped_lock l(m_mutex);
      if(m_current_precision < boost::math::tools::digits<T>())
      {
         bn.clear();
         tn.clear();
         m_intermediates.clear();
         m_current_precision = boost::math::tools::digits<T>();
      }
      if(start + n >= bn.size())
      {
         std::size_t new_size = (std::min)((std::max)((std::max)(start + n, std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
         tangent_numbers_series(new_size);
      }

      for(std::size_t i = start; i < start + n; ++i)
      {
         if(i >= m_overflow_limit)
            *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
         else
         {
            if(tools::max_value<T>() * tangent_scale_factor<T>() < tn[static_cast<typename container_type::size_type>(i)])
               *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
            else
               *out = tn[static_cast<typename container_type::size_type>(i)] / tangent_scale_factor<T>();
         }
         ++out;
      }

   #else
      //
      // Double-checked locking pattern, lets us access cached already cached values
      // without locking:
      //
      // Get the counter and see if we need to calculate more constants:
      //
      if((static_cast<std::size_t>(m_counter.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < start + n)
         || (static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>()))
      {
         boost::detail::lightweight_mutex::scoped_lock l(m_mutex);

         if((static_cast<std::size_t>(m_counter.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < start + n)
            || (static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>()))
         {
            if(static_cast<int>(m_current_precision.load(BOOST_MATH_ATOMIC_NS::memory_order_consume)) < boost::math::tools::digits<T>())
            {
               bn.clear();
               tn.clear();
               m_intermediates.clear();
               m_counter.store(0, BOOST_MATH_ATOMIC_NS::memory_order_release);
               m_current_precision = boost::math::tools::digits<T>();
            }
            if(start + n >= bn.size())
            {
               std::size_t new_size = (std::min)((std::max)((std::max)(start + n, std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
               tangent_numbers_series(new_size);
            }
            m_counter.store(static_cast<atomic_integer_type>(bn.size()), BOOST_MATH_ATOMIC_NS::memory_order_release);
         }
      }

      for(std::size_t i = start; i < start + n; ++i)
      {
         if(i >= m_overflow_limit)
            *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
         else
         {
            if(tools::max_value<T>() * tangent_scale_factor<T>() < tn[static_cast<typename container_type::size_type>(i)])
               *out = policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol);
            else
               *out = tn[static_cast<typename container_type::size_type>(i)] / tangent_scale_factor<T>();
         }
         ++out;
      }

   #endif
      return out;
   }

private:
   //
   // The caches for Bernoulli and tangent numbers, once allocated,
   // these must NEVER EVER reallocate as it breaks our thread
   // safety guarantees:
   //
   fixed_vector<T> bn, tn;
   std::vector<T> m_intermediates;
   // The value at which we know overflow has already occurred for the Bn:
   std::size_t m_overflow_limit;
#if !defined(BOOST_HAS_THREADS)
   int m_current_precision;
#elif defined(BOOST_MATH_NO_ATOMIC_INT)
   boost::detail::lightweight_mutex m_mutex;
   int m_current_precision;
#else
   boost::detail::lightweight_mutex m_mutex;
   atomic_counter_type m_counter, m_current_precision;
#endif
};

template <class T, class Policy>
inline bernoulli_numbers_cache<T, Policy>& get_bernoulli_numbers_cache()
{
   //
   // Force this function to be called at program startup so all the static variables
   // get initialized then (thread safety).
   //
   bernoulli_initializer<T, Policy>::force_instantiate();
   static bernoulli_numbers_cache<T, Policy> data;
   return data;
}

}}}

#endif // BOOST_MATH_BERNOULLI_DETAIL_HPP

/* bernoulli_details.hpp
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
*/