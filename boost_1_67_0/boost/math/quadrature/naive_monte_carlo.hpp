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
#include <boost/atomic.hpp>
#include <functional>
#include <future>
#include <thread>
#include <initializer_list>
#include <utility>
#include <random>
#include <chrono>
#include <map>
#include <boost/math/policies/error_handling.hpp>

namespace boost { namespace math { namespace quadrature {

namespace detail {
  enum class limit_classification {FINITE,
                                   LOWER_BOUND_INFINITE,
                                   UPPER_BOUND_INFINITE,
                                   DOUBLE_INFINITE};
}

template<class Real, class F, class RandomNumberGenerator = std::mt19937_64, class Policy = boost::math::policies::policy<>>
class naive_monte_carlo
{
public:
    naive_monte_carlo(const F& integrand,
                      std::vector<std::pair<Real, Real>> const & bounds,
                      Real error_goal,
                      bool singular = true,
                      uint64_t threads = std::thread::hardware_concurrency(),
                      uint64_t seed = 0): m_num_threads{threads}, m_seed{seed}
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

        m_num_threads = (std::max)(m_num_threads, (uint64_t) 1);
        m_thread_calls.reset(new boost::atomic<uint64_t>[threads]);
        m_thread_Ss.reset(new boost::atomic<Real>[threads]);
        m_thread_averages.reset(new boost::atomic<Real>[threads]);

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
               uint64_t t_calls = m_thread_calls[i].load(boost::memory_order::consume);
               total_calls += t_calls;
            }
            Real variance = 0;
            Real avg = 0;
            for (uint64_t i = 0; i < m_num_threads; ++i)
            {
               uint64_t t_calls = m_thread_calls[i].load(boost::memory_order::consume);
               // Will this overflow? Not hard to remove . . .
               avg += m_thread_averages[i].load(boost::memory_order::relaxed)*((Real)t_calls / (Real)total_calls);
               variance += m_thread_Ss[i].load(boost::memory_order::relaxed);
            }
            m_avg.store(avg, boost::memory_order::release);
            m_variance.store(variance / (total_calls - 1), boost::memory_order::release);
            m_total_calls = total_calls; // relaxed store, it's just for user feedback
            // Allow cancellation:
            if (m_done) // relaxed load
            {
               break;
            }
         } while (m_total_calls < 2048 || this->current_error_estimate() > m_error_goal.load(boost::memory_order::consume));
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
            uint64_t t_calls = m_thread_calls[i].load(boost::memory_order::consume);
            total_calls += t_calls;
         }
         Real variance = 0;
         Real avg = 0;

         for (uint64_t i = 0; i < m_num_threads; ++i)
         {
            uint64_t t_calls = m_thread_calls[i].load(boost::memory_order::consume);
            // Averages weighted by the number of calls the thread made:
            avg += m_thread_averages[i].load(boost::memory_order::relaxed)*((Real)t_calls / (Real)total_calls);
            variance += m_thread_Ss[i].load(boost::memory_order::relaxed);
         }
         m_avg.store(avg, boost::memory_order::release);
         m_variance.store(variance / (total_calls - 1), boost::memory_order::release);
         m_total_calls = total_calls; // relaxed store, this is just user feedback

         // Sometimes, the master will observe the variance at a very "good" (or bad?) moment,
         // Then the threads proceed to find the variance is much greater by the time they hear the message to stop.
         // This *WOULD* make sure that the final error estimate is within the error bounds.
      }
      while ((--max_repeat_tries >= 0) && (this->current_error_estimate() > m_error_goal));

      return m_avg.load(boost::memory_order::consume);
    }

    void m_thread_monte(uint64_t thread_index, uint64_t seed)
    {
        using std::numeric_limits;
        try
        {
            std::vector<Real> x(m_lbs.size());
            RandomNumberGenerator gen(seed);
            Real inv_denom = (Real) 1/(Real)( (gen.max)() - (gen.min)()  );
            Real M1 = m_thread_averages[thread_index].load(boost::memory_order::consume);
            Real S = m_thread_Ss[thread_index].load(boost::memory_order::consume);
            // Kahan summation is required or the value of the integrand will go on a random walk during long computations.
            // See the implementation discussion.
            // The idea is that the unstabilized additions have error sigma(f)/sqrt(N) + epsilon*N, which diverges faster than it converges!
            // Kahan summation turns this to sigma(f)/sqrt(N) + epsilon^2*N, and the random walk occurs on a timescale of 10^14 years (on current hardware)
            Real compensator = 0;
            uint64_t k = m_thread_calls[thread_index].load(boost::memory_order::consume);
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
                m_thread_averages[thread_index].store(M1, boost::memory_order::release);
                m_thread_Ss[thread_index].store(S, boost::memory_order::release);
                m_thread_calls[thread_index].store(k, boost::memory_order::release);
            }
        }
        catch (...)
        {
            // Signal the other threads that the computation is ruined:
            m_done = true; // relaxed store
            m_exception = std::current_exception();
        }
    }

    std::function<Real(std::vector<Real> &)> m_integrand;
    uint64_t m_num_threads;
    uint64_t m_seed;
    boost::atomic<Real> m_error_goal;
    boost::atomic<bool> m_done;
    std::vector<Real> m_lbs;
    std::vector<Real> m_dxs;
    std::vector<detail::limit_classification> m_limit_types;
    Real m_volume;
    boost::atomic<uint64_t> m_total_calls;
    // I wanted these to be vectors rather than maps,
    // but you can't resize a vector of atomics.
    std::unique_ptr<boost::atomic<uint64_t>[]> m_thread_calls;
    boost::atomic<Real> m_variance;
    std::unique_ptr<boost::atomic<Real>[]> m_thread_Ss;
    boost::atomic<Real> m_avg;
    std::unique_ptr<boost::atomic<Real>[]> m_thread_averages;
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::exception_ptr m_exception;
};

}}}
#endif

/* naive_monte_carlo.hpp
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
*/