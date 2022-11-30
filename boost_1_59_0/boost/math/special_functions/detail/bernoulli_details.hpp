///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BERNOULLI_DETAIL_HPP
#define BOOST_MATH_BERNOULLI_DETAIL_HPP

#include <boost/math/tools/atomic.hpp>
#include <boost/math/tools/toms748_solve.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#include <boost/math/tools/throw_exception.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <vector>
#include <type_traits>

#if defined(BOOST_HAS_THREADS) && !defined(BOOST_NO_CXX11_HDR_MUTEX) && !defined(BOOST_MATH_NO_ATOMIC_INT)
#include <mutex>
#else
#  define BOOST_MATH_BERNOULLI_NOTHREADS
#endif

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
   max_bernoulli_root_functor(unsigned long long t) : target(static_cast<double>(t)) {}
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
inline std::size_t find_bernoulli_overflow_limit(const std::false_type&)
{
   // Set a limit on how large the result can ever be:
   static const double max_result = static_cast<double>((std::numeric_limits<std::size_t>::max)() - 1000u);

   unsigned long long t = lltrunc(boost::math::tools::log_max_value<T>());
   max_bernoulli_root_functor fun(t);
   boost::math::tools::equal_floor tol;
   std::uintmax_t max_iter = boost::math::policies::get_max_root_iterations<Policy>();
   double result = boost::math::tools::toms748_solve(fun, sqrt(double(t)), double(t), tol, max_iter).first / 2;
   if (result > max_result)
      result = max_result;
   
   return static_cast<std::size_t>(result);
}

template <class T, class Policy>
inline std::size_t find_bernoulli_overflow_limit(const std::true_type&)
{
   return max_bernoulli_index<bernoulli_imp_variant<T>::value>::value;
}

template <class T, class Policy>
std::size_t b2n_overflow_limit()
{
   // This routine is called at program startup if it's called at all:
   // that guarantees safe initialization of the static variable.
   typedef std::integral_constant<bool, (bernoulli_imp_variant<T>::value >= 1) && (bernoulli_imp_variant<T>::value <= 3)> tag_type;
   static const std::size_t lim = find_bernoulli_overflow_limit<T, Policy>(tag_type());
   return lim;
}

//
// The tangent numbers grow larger much more rapidly than the Bernoulli numbers do....
// so to compute the Bernoulli numbers from the tangent numbers, we need to avoid spurious
// overflow in the calculation, we can do this by scaling all the tangent number by some scale factor:
//
template <class T, typename std::enable_if<std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::radix == 2), bool>::type = true>
inline T tangent_scale_factor()
{
   BOOST_MATH_STD_USING
   return ldexp(T(1), std::numeric_limits<T>::min_exponent + 5);
}

template <class T, typename std::enable_if<!std::numeric_limits<T>::is_specialized || !(std::numeric_limits<T>::radix == 2), bool>::type = true>
inline T tangent_scale_factor()
{
   return tools::min_value<T>() * 16;
}

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
      typedef std::allocator<T> allocator_type;
      typedef std::allocator_traits<allocator_type> allocator_traits; 
      allocator_type& alloc = *this; 
      for(unsigned i = 0; i < m_used; ++i)
         allocator_traits::destroy(alloc, &m_data[i]);
      allocator_traits::deallocate(alloc, m_data, m_capacity);
   }
   T& operator[](unsigned n) { BOOST_MATH_ASSERT(n < m_used); return m_data[n]; }
   const T& operator[](unsigned n)const { BOOST_MATH_ASSERT(n < m_used); return m_data[n]; }
   unsigned size()const { return m_used; }
   unsigned size() { return m_used; }
   void resize(unsigned n, const T& val)
   {
      if(n > m_capacity)
      {
         BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Exhausted storage for Bernoulli numbers."));
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
      , m_counter(0)
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

      #if defined(BOOST_HAS_THREADS) && defined(BOOST_MATH_BERNOULLI_NOTHREADS) && !defined(BOOST_MATH_BERNOULLI_UNTHREADED)
      // Add a static_assert on instantiation if we have threads, but no C++11 threading support.
      static_assert(sizeof(T) == 1, "Unsupported configuration: your platform appears to have either no atomic integers, or no std::mutex.  If you are happy with thread-unsafe code, then you may define BOOST_MATH_BERNOULLI_UNTHREADED to suppress this error.");
      #elif defined(BOOST_MATH_BERNOULLI_NOTHREADS)
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
      #else
      //
      // Double-checked locking pattern, lets us access cached already cached values
      // without locking:
      //
      // Get the counter and see if we need to calculate more constants:
      //
      if((static_cast<std::size_t>(m_counter.load(std::memory_order_consume)) < start + n)
         || (static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>()))
      {
         std::lock_guard<std::mutex> l(m_mutex);

         if((static_cast<std::size_t>(m_counter.load(std::memory_order_consume)) < start + n)
            || (static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>()))
         {
            if(static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>())
            {
               bn.clear();
               tn.clear();
               m_intermediates.clear();
               m_counter.store(0, std::memory_order_release);
               m_current_precision = boost::math::tools::digits<T>();
            }
            if(start + n >= bn.size())
            {
               std::size_t new_size = (std::min)((std::max)((std::max)(std::size_t(start + n), std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
               tangent_numbers_series(new_size);
            }
            m_counter.store(static_cast<atomic_integer_type>(bn.size()), std::memory_order_release);
         }
      }

      for(std::size_t i = (std::max)(static_cast<std::size_t>(max_bernoulli_b2n<T>::value + 1), start); i < start + n; ++i)
      {
         *out = (i >= m_overflow_limit) ? policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(std::size_t)", 0, T(i), pol) : bn[static_cast<typename container_type::size_type>(i)];
         ++out;
      }

      #endif // BOOST_HAS_THREADS
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

      #if defined(BOOST_MATH_BERNOULLI_NOTHREADS)
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
      static_assert(sizeof(T) == 1, "Unsupported configuration: your platform appears to have no atomic integers.  If you are happy with thread-unsafe code, then you may define BOOST_MATH_BERNOULLI_UNTHREADED to suppress this error.");
      #else
      //
      // Double-checked locking pattern, lets us access cached already cached values
      // without locking:
      //
      // Get the counter and see if we need to calculate more constants:
      //
      if((static_cast<std::size_t>(m_counter.load(std::memory_order_consume)) < start + n)
         || (static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>()))
      {
         std::lock_guard<std::mutex> l(m_mutex);

         if((static_cast<std::size_t>(m_counter.load(std::memory_order_consume)) < start + n)
            || (static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>()))
         {
            if(static_cast<int>(m_current_precision.load(std::memory_order_consume)) < boost::math::tools::digits<T>())
            {
               bn.clear();
               tn.clear();
               m_intermediates.clear();
               m_counter.store(0, std::memory_order_release);
               m_current_precision = boost::math::tools::digits<T>();
            }
            if(start + n >= bn.size())
            {
               std::size_t new_size = (std::min)((std::max)((std::max)(start + n, std::size_t(bn.size() + 20)), std::size_t(50)), std::size_t(bn.capacity()));
               tangent_numbers_series(new_size);
            }
            m_counter.store(static_cast<atomic_integer_type>(bn.size()), std::memory_order_release);
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

      #endif // BOOST_HAS_THREADS
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

   #if !defined(BOOST_MATH_BERNOULLI_NOTHREADS)
   std::mutex m_mutex;
   atomic_counter_type m_counter, m_current_precision;
   #else
   int m_counter;
   int m_current_precision;
   #endif // BOOST_HAS_THREADS
};

template <class T, class Policy>
inline typename std::enable_if<(std::numeric_limits<T>::digits == 0) || (std::numeric_limits<T>::digits >= INT_MAX), bernoulli_numbers_cache<T, Policy>&>::type get_bernoulli_numbers_cache()
{
   //
   // When numeric_limits<>::digits is zero, the type has either not specialized numeric_limits at all
   // or it's precision can vary at runtime.  So make the cache thread_local so that each thread can
   // have it's own precision if required:
   //
   static 
#ifndef BOOST_MATH_NO_THREAD_LOCAL_WITH_NON_TRIVIAL_TYPES
      BOOST_MATH_THREAD_LOCAL
#endif
      bernoulli_numbers_cache<T, Policy> data;
   return data;
}
template <class T, class Policy>
inline typename std::enable_if<std::numeric_limits<T>::digits && (std::numeric_limits<T>::digits < INT_MAX), bernoulli_numbers_cache<T, Policy>&>::type get_bernoulli_numbers_cache()
{
   //
   // Note that we rely on C++11 thread-safe initialization here:
   //
   static bernoulli_numbers_cache<T, Policy> data;
   return data;
}

}}}

#endif // BOOST_MATH_BERNOULLI_DETAIL_HPP

/* bernoulli_details.hpp
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
*/