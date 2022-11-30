/*
 * Copyright Nick Thompson, 2018
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_MATH_QUADRATURE_NAIVE_MONTE_CARLO_HPP
#define BOOST_MATH_QUADRATURE_NAIVE_MONTE_CARLO_HPP
#include <sstream>
#include <algorithm>
#include <vector>
#include <atomic>
#include <memory>
#include <functional>
#include <future>
#include <thread>
#include <initializer_list>
#include <utility>
#include <random>
#include <chrono>
#include <map>
#include <type_traits>
#include <boost/math/policies/error_handling.hpp>

namespace boost { namespace math { namespace quadrature {

namespace detail {
  enum class limit_classification {FINITE,
                                   LOWER_BOUND_INFINITE,
                                   UPPER_BOUND_INFINITE,
                                   DOUBLE_INFINITE};
}

template<class Real, class F, class RandomNumberGenerator = std::mt19937_64, class Policy = boost::math::policies::policy<>,
         typename std::enable_if<std::is_trivially_copyable<Real>::value, bool>::type = true>
class naive_monte_carlo
{
public:
    naive_monte_carlo(const F& integrand,
                      std::vector<std::pair<Real, Real>> const & bounds,
                      Real error_goal,
                      bool singular = true,
                      uint64_t threads = std::thread::hardware_concurrency(),
                      uint64_t seed = 0) noexcept : m_num_threads{threads}, m_seed{seed}
    {
        using std::numeric_limits;
        using std::sqrt;
        uint64_t n = bounds.size();
        m_lbs.resize(n);
        m_dxs.resize(n);
        m_limit_types.resize(n);
        m_volume = 1;
        static const char* function = "boost::math::quadrature::naive_monte_carlo<%1%>";
        for (uint64_t i = 0; i < n; ++i)
        {
            if (bounds[i].second <= bounds[i].first)
            {
                boost::math::policies::raise_domain_error(function, "The upper bound is <= the lower bound.\n", bounds[i].second, Policy());
                return;
            }
            if (bounds[i].first == -numeric_limits<Real>::infinity())
            {
                if (bounds[i].second == numeric_limits<Real>::infinity())
                {
                    m_limit_types[i] = detail::limit_classification::DOUBLE_INFINITE;
                }
                else
                {
                    m_limit_types[i] = detail::limit_classification::LOWER_BOUND_INFINITE;
                    // Ok ok this is bad to use the second bound as the lower limit and then reflect.
                    m_lbs[i] = bounds[i].second;
                    m_dxs[i] = numeric_limits<Real>::quiet_NaN();
                }
            }
            else if (bounds[i].second == numeric_limits<Real>::infinity())
            {
                m_limit_types[i] = detail::limit_classification::UPPER_BOUND_INFINITE;
                if (singular)
                {
                    // I've found that it's easier to sample on a closed set and perturb the boundary
                    // than to try to sample very close to the boundary.
                    m_lbs[i] = std::nextafter(bounds[i].first, (std::numeric_limits<Real>::max)());
                }
                else
                {
                    m_lbs[i] = bounds[i].first;
                }
                m_dxs[i] = numeric_limits<Real>::quiet_NaN();
            }
            else
            {
                m_limit_types[i] = detail::limit_classification::FINITE;
                if (singular)
                {
                    if (bounds[i].first == 0)
                    {
                        m_lbs[i] = std::numeric_limits<Real>::epsilon();
                    }
                    else
                    {
                        m_lbs[i] = std::nextafter(bounds[i].first, (std::numeric_limits<Real>::max)());
                    }

                    m_dxs[i] = std::nextafter(bounds[i].second, std::numeric_limits<Real>::lowest()) - m_lbs[i];
                }
                else
                {
                    m_lbs[i] = bounds[i].first;
                    m_dxs[i] = bounds[i].second - bounds[i].first;
                }
                m_volume *= m_dxs[i];
            }
        }

        m_integrand = [this, &integrand](std::vector<Real> & x)->Real
        {
            Real coeff = m_volume;
            for (uint64_t i = 0; i < x.size(); ++i)
            {
                // Variable transformation are listed at:
                // https://en.wikipedia.org/wiki/Numerical_integration
                // However, we've made some changes to these so that we can evaluate on a compact domain.
                if (m_limit_types[i] == detail::limit_classification::FINITE)
                {
                    x[i] = m_lbs[i] + x[i]*m_dxs[i];
                }
                else if (m_limit_types[i] == detail::limit_classification::UPPER_BOUND_INFINITE)
                {
                    Real t = x[i];
                    Real z = 1/(1 + numeric_limits<Real>::epsilon() - t);
                    coeff *= (z*z)*(1 + numeric_limits<Real>::epsilon());
                    x[i] = m_lbs[i] + t*z;
                }
                else if (m_limit_types[i] == detail::limit_classification::LOWER_BOUND_INFINITE)
                {
                    Real t = x[i];
                    Real z = 1/(t+sqrt((numeric_limits<Real>::min)()));
                    coeff *= (z*z);
                    x[i] = m_lbs[i] + (t-1)*z;
                }
                else
                {
                    Real t1 = 1/(1+numeric_limits<Real>::epsilon() - x[i]);
                    Real t2 = 1/(x[i]+numeric_limits<Real>::epsilon());
                    x[i] = (2*x[i]-1)*t1*t2/4;
                    coeff *= (t1*t1+t2*t2)/4;
                }
            }
            return coeff*integrand(x);
        };

        // If we don't do a single function call in the constructor,
        // we can't do a restart.
        std::vector<Real> x(m_lbs.size());

        // If the seed is zero, that tells us to choose a random seed for the user:
        if (seed == 0)
        {
            std::random_device rd;
            seed = rd();
        }

        RandomNumberGenerator gen(seed);
        Real inv_denom = 1/static_cast<Real>(((gen.max)()-(gen.min)()));

        m_num_threads = (std::max)(m_num_threads, static_cast<uint64_t>(1));
        m_thread_calls.reset(new std::atomic<uint64_t>[threads]);
        m_thread_Ss.reset(new std::atomic<Real>[threads]);
        m_thread_averages.reset(new std::atomic<Real>[threads]);

        Real avg = 0;
        for (uint64_t i = 0; i < m_num_threads; ++i)
        {
            for (uint64_t j = 0; j < m_lbs.size(); ++j)
            {
                x[j] = (gen()-(gen.min)())*inv_denom;
            }
            Real y = m_integrand(x);
            m_thread_averages[i] = y; // relaxed store
            m_thread_calls[i] = 1;
            m_thread_Ss[i] = 0;
            avg += y;
        }
        avg /= m_num_threads;
        m_avg = avg; // relaxed store

        m_error_goal = error_goal; // relaxed store
        m_start = std::chrono::system_clock::now();
        m_done = false; // relaxed store
        m_total_calls = m_num_threads;  // relaxed store
        m_variance = (numeric_limits<Real>::max)();
    }

    std::future<Real> integrate()
    {
        // Set done to false in case we wish to restart:
        m_done.store(false); // relaxed store, no worker threads yet
        m_start = std::chrono::system_clock::now();
        return std::async(std::launch::async,
                          &naive_monte_carlo::m_integrate, this);
    }

    void cancel()
    {
        // If seed = 0 (meaning have the routine pick the seed), this leaves the seed the same.
        // If seed != 0, then the seed is changed, so a restart doesn't do the exact same thing.
        m_seed = m_seed*m_seed;
        m_done = true; // relaxed store, worker threads will get the message eventually
        // Make sure the error goal is infinite, because otherwise we'll loop when we do the final error goal check:
        m_error_goal = (std::numeric_limits<Real>::max)();
    }

    Real variance() const
    {
        return m_variance.load();
    }

    Real current_error_estimate() const
    {
        using std::sqrt;
        //
        // There is a bug here: m_variance and m_total_calls get updated asynchronously
        // and may be out of synch when we compute the error estimate, not sure if it matters though...
        //
        return sqrt(m_variance.load()/m_total_calls.load());
    }

    std::chrono::duration<Real> estimated_time_to_completion() const
    {
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<Real> elapsed_seconds = now - m_start;
        Real r = this->current_error_estimate()/m_error_goal.load(); // relaxed load
        if (r*r <= 1) {
            return 0*elapsed_seconds;
        }
        return (r*r - 1)*elapsed_seconds;
    }

    void update_target_error(Real new_target_error)
    {
        m_error_goal = new_target_error;  // relaxed store
    }

    Real progress() const
    {
        Real r = m_error_goal.load()/this->current_error_estimate();  // relaxed load
        if (r*r >= 1)
        {
            return 1;
        }
        return r*r;
    }

    Real current_estimate() const
    {
        return m_avg.load();
    }

    uint64_t calls() const
    {
        return m_total_calls.load();  // relaxed load
    }

private:

   Real m_integrate()
   {
      uint64_t seed;
      // If the user tells us to pick a seed, pick a seed:
      if (m_seed == 0)
      {
         std::random_device rd;
         seed = rd();
      }
      else // use the seed we are given:
      {
         seed = m_seed;
      }
      RandomNumberGenerator gen(seed);
      int max_repeat_tries = 5;
      do{

         if (max_repeat_tries < 5)
         {
            m_done = false;

#ifdef BOOST_NAIVE_MONTE_CARLO_DEBUG_FAILURES
            std::cout << "Failed to achieve required tolerance first time through..\n";
            std::cout << "  variance =    " << m_variance << std::endl;
            std::cout << "  average =     " << m_avg << std::endl;
            std::cout << "  total calls = " << m_total_calls << std::endl;

            for (std::size_t i = 0; i < m_num_threads; ++i)
               std::cout << "  thread_calls[" << i << "] = " << m_thread_calls[i] << std::endl;
            for (std::size_t i = 0; i < m_num_threads; ++i)
               std::cout << "  thread_averages[" << i << "] = " << m_thread_averages[i] << std::endl;
            for (std::size_t i = 0; i < m_num_threads; ++i)
               std::cout << "  thread_Ss[" << i << "] = " << m_thread_Ss[i] << std::endl;
#endif
         }

         std::vector<std::thread> threads(m_num_threads);
         for (uint64_t i = 0; i < threads.size(); ++i)
         {
            threads[i] = std::thread(&naive_monte_carlo::m_thread_monte, this, i, gen());
         }
         do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            uint64_t total_calls = 0;
            for (uint64_t i = 0; i < m_num_threads; ++i)
            {
               uint64_t t_calls = m_thread_calls[i].load(std::memory_order_consume);
               total_calls += t_calls;
            }
            Real variance = 0;
            Real avg = 0;
            for (uint64_t i = 0; i < m_num_threads; ++i)
            {
               uint64_t t_calls = m_thread_calls[i].load(std::memory_order_consume);
               // Will this overflow? Not hard to remove . . .
               avg += m_thread_averages[i].load(std::memory_order_relaxed)*(static_cast<Real>(t_calls) / static_cast<Real>(total_calls));
               variance += m_thread_Ss[i].load(std::memory_order_relaxed);
            }
            m_avg.store(avg, std::memory_order_release);
            m_variance.store(variance / (total_calls - 1), std::memory_order_release);
            m_total_calls = total_calls; // relaxed store, it's just for user feedback
            // Allow cancellation:
            if (m_done) // relaxed load
            {
               break;
            }
         } while (m_total_calls < 2048 || this->current_error_estimate() > m_error_goal.load(std::memory_order_consume));
         // Error bound met; signal the threads:
         m_done = true; // relaxed store, threads will get the message in the end
         std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));
         if (m_exception)
         {
            std::rethrow_exception(m_exception);
         }
         // Incorporate their work into the final estimate:
         uint64_t total_calls = 0;
         for (uint64_t i = 0; i < m_num_threads; ++i)
         {
            uint64_t t_calls = m_thread_calls[i].load(std::memory_order_consume);
            total_calls += t_calls;
         }
         Real variance = 0;
         Real avg = 0;

         for (uint64_t i = 0; i < m_num_threads; ++i)
         {
            uint64_t t_calls = m_thread_calls[i].load(std::memory_order_consume);
            // Averages weighted by the number of calls the thread made:
            avg += m_thread_averages[i].load(std::memory_order_relaxed)*(static_cast<Real>(t_calls) / static_cast<Real>(total_calls));
            variance += m_thread_Ss[i].load(std::memory_order_relaxed);
         }
         m_avg.store(avg, std::memory_order_release);
         m_variance.store(variance / (total_calls - 1), std::memory_order_release);
         m_total_calls = total_calls; // relaxed store, this is just user feedback

         // Sometimes, the master will observe the variance at a very "good" (or bad?) moment,
         // Then the threads proceed to find the variance is much greater by the time they hear the message to stop.
         // This *WOULD* make sure that the final error estimate is within the error bounds.
      }
      while ((--max_repeat_tries >= 0) && (this->current_error_estimate() > m_error_goal));

      return m_avg.load(std::memory_order_consume);
    }

    void m_thread_monte(uint64_t thread_index, uint64_t seed)
    {
        using std::numeric_limits;
        try
        {
            std::vector<Real> x(m_lbs.size());
            RandomNumberGenerator gen(seed);
            Real inv_denom = static_cast<Real>(1) / static_cast<Real>(( (gen.max)() - (gen.min)() ));
            Real M1 = m_thread_averages[thread_index].load(std::memory_order_consume);
            Real S = m_thread_Ss[thread_index].load(std::memory_order_consume);
            // Kahan summation is required or the value of the integrand will go on a random walk during long computations.
            // See the implementation discussion.
            // The idea is that the unstabilized additions have error sigma(f)/sqrt(N) + epsilon*N, which diverges faster than it converges!
            // Kahan summation turns this to sigma(f)/sqrt(N) + epsilon^2*N, and the random walk occurs on a timescale of 10^14 years (on current hardware)
            Real compensator = 0;
            uint64_t k = m_thread_calls[thread_index].load(std::memory_order_consume);
            while (!m_done) // relaxed load
            {
                int j = 0;
                // If we don't have a certain number of calls before an update, we can easily terminate prematurely
                // because the variance estimate is way too low. This magic number is a reasonable compromise, as 1/sqrt(2048) = 0.02,
                // so it should recover 2 digits if the integrand isn't poorly behaved, and if it is, it should discover that before premature termination.
                // Of course if the user has 64 threads, then this number is probably excessive.
                int magic_calls_before_update = 2048;
                while (j++ < magic_calls_before_update)
                {
                    for (uint64_t i = 0; i < m_lbs.size(); ++i)
                    {
                        x[i] = (gen() - (gen.min)())*inv_denom;
                    }
                    Real f = m_integrand(x);
                    using std::isfinite;
                    if (!isfinite(f))
                    {
                        // The call to m_integrand transform x, so this error message states the correct node.
                        std::stringstream os;
                        os << "Your integrand was evaluated at {";
                        for (uint64_t i = 0; i < x.size() -1; ++i)
                        {
                             os << x[i] << ", ";
                        }
                        os << x[x.size() -1] << "}, and returned " << f << std::endl;
                        static const char* function = "boost::math::quadrature::naive_monte_carlo<%1%>";
                        boost::math::policies::raise_domain_error(function, os.str().c_str(), /*this is a dummy arg to make it compile*/ 7.2, Policy());
                    }
                    ++k;
                    Real term = (f - M1)/k;
                    Real y1 = term - compensator;
                    Real M2 = M1 + y1;
                    compensator = (M2 - M1) - y1;
                    S += (f - M1)*(f - M2);
                    M1 = M2;
                }
                m_thread_averages[thread_index].store(M1, std::memory_order_release);
                m_thread_Ss[thread_index].store(S, std::memory_order_release);
                m_thread_calls[thread_index].store(k, std::memory_order_release);
            }
        }
        catch (...)
        {
            // Signal the other threads that the computation is ruined:
            m_done = true; // relaxed store
            std::lock_guard<std::mutex> lock(m_exception_mutex); // Scoped lock to prevent race writing to m_exception
            m_exception = std::current_exception();
        }
    }

    std::function<Real(std::vector<Real> &)> m_integrand;
    uint64_t m_num_threads;
    std::atomic<uint64_t> m_seed;
    std::atomic<Real> m_error_goal;
    std::atomic<bool> m_done;
    std::vector<Real> m_lbs;
    std::vector<Real> m_dxs;
    std::vector<detail::limit_classification> m_limit_types;
    Real m_volume;
    std::atomic<uint64_t> m_total_calls;
    // I wanted these to be vectors rather than maps,
    // but you can't resize a vector of atomics.
    std::unique_ptr<std::atomic<uint64_t>[]> m_thread_calls;
    std::atomic<Real> m_variance;
    std::unique_ptr<std::atomic<Real>[]> m_thread_Ss;
    std::atomic<Real> m_avg;
    std::unique_ptr<std::atomic<Real>[]> m_thread_averages;
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::exception_ptr m_exception;
    std::mutex m_exception_mutex;
};

}}}
#endif

/* naive_monte_carlo.hpp
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
*/