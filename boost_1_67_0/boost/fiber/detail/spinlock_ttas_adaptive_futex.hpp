
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H
#define BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H

#include <atomic>
#include <cmath>
#include <random>
#include <thread>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/cpu_relax.hpp>
#include <boost/fiber/detail/futex.hpp>

// based on informations from:
// https://software.intel.com/en-us/articles/benefitting-power-and-performance-sleep-loops
// https://software.intel.com/en-us/articles/long-duration-spin-wait-loops-on-hyper-threading-technology-enabled-intel-processors

namespace boost {
namespace fibers {
namespace detail {

class spinlock_ttas_adaptive_futex {
private:
    template< typename FBSplk >
    friend class spinlock_rtm;

    std::atomic< std::int32_t >                 value_{ 0 };
    std::atomic< std::int32_t >                 retries_{ 0 };

public:
    spinlock_ttas_adaptive_futex() = default;

    spinlock_ttas_adaptive_futex( spinlock_ttas_adaptive_futex const&) = delete;
    spinlock_ttas_adaptive_futex & operator=( spinlock_ttas_adaptive_futex const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::int32_t collisions = 0, retries = 0, expected = 0;
        const std::int32_t prev_retries = retries_.load( std::memory_order_relaxed);
        const std::int32_t max_relax_retries = (std::min)(
                static_cast< std::int32_t >( BOOST_FIBERS_SPIN_BEFORE_SLEEP0), 2 * prev_retries + 10);
        const std::int32_t max_sleep_retries = (std::min)(
                static_cast< std::int32_t >( BOOST_FIBERS_SPIN_BEFORE_YIELD), 2 * prev_retries + 10);
        // after max. spins or collisions suspend via futex
        while ( retries++ < BOOST_FIBERS_RETRY_THRESHOLD) {
            // avoid using multiple pause instructions for a delay of a specific cycle count
            // the delay of cpu_relax() (pause on Intel) depends on the processor family
            // the cycle count can not guaranteed from one system to the next
            // -> check the shared variable 'value_' in between each cpu_relax() to prevent
            //    unnecessarily long delays on some systems
            // test shared variable 'status_'
            // first access to 'value_' -> chache miss
            // sucessive acccess to 'value_' -> cache hit
            // if 'value_' was released by other fiber
            // cached 'value_' is invalidated -> cache miss
            if ( 0 != ( expected = value_.load( std::memory_order_relaxed) ) ) {
#if !defined(BOOST_FIBERS_SPIN_SINGLE_CORE)
                if ( max_relax_retries > retries) {
                    // give CPU a hint that this thread is in a "spin-wait" loop
                    // delays the next instruction's execution for a finite period of time (depends on processor family)
                    // the CPU is not under demand, parts of the pipeline are no longer being used
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                } else if ( max_sleep_retries > retries) {
                    // std::this_thread::sleep_for( 0us) has a fairly long instruction path length,
                    // combined with an expensive ring3 to ring 0 transition costing about 1000 cycles
                    // std::this_thread::sleep_for( 0us) lets give up this_thread the remaining part of its time slice
                    // if and only if a thread of equal or greater priority is ready to run
                    static constexpr std::chrono::microseconds us0{ 0 };
                    std::this_thread::sleep_for( us0);
                } else {
                    // std::this_thread::yield() allows this_thread to give up the remaining part of its time slice,
                    // but only to another thread on the same processor
                    // instead of constant checking, a thread only checks if no other useful work is pending
                    std::this_thread::yield();
                }
#else
                // std::this_thread::yield() allows this_thread to give up the remaining part of its time slice,
                // but only to another thread on the same processor
                // instead of constant checking, a thread only checks if no other useful work is pending
                std::this_thread::yield();
#endif
            } else if ( ! value_.compare_exchange_strong( expected, 1, std::memory_order_acquire) ) {
                // spinlock now contended
                // utilize 'Binary Exponential Backoff' algorithm
                // linear_congruential_engine is a random number engine based on Linear congruential generator (LCG)
                std::uniform_int_distribution< std::int32_t > distribution{
                    0, static_cast< std::int32_t >( 1) << (std::min)(collisions, static_cast< std::int32_t >( BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)) };
                const std::int32_t z = distribution( generator);
                ++collisions;
                for ( std::int32_t i = 0; i < z; ++i) {
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                }
            } else {
                // success, lock acquired
                retries_.store( prev_retries + (retries - prev_retries) / 8, std::memory_order_relaxed);
                return;
            }
        }
        // failure, lock not acquired
        // pause via futex
        if ( 2 != expected) {
            expected = value_.exchange( 2, std::memory_order_acquire);
        }
        while ( 0 != expected) {
            futex_wait( & value_, 2);
            expected = value_.exchange( 2, std::memory_order_acquire);
        }
        // success, lock acquired
        retries_.store( prev_retries + (retries - prev_retries) / 8, std::memory_order_relaxed);
    }

    bool try_lock() noexcept {
        std::int32_t expected = 0;
        return value_.compare_exchange_strong( expected, 1, std::memory_order_acquire);
    }

    void unlock() noexcept {
        if ( 1 != value_.fetch_sub( 1, std::memory_order_acquire) ) {
            value_.store( 0, std::memory_order_release);
            futex_wake( & value_);
        }
    }
};

}}}

#endif // BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H

/* spinlock_ttas_adaptive_futex.hpp
j4ODkZVoAGUPfUCs+BcQMkQsiAY3bXA+IW2QUYj4gNjf3eIO/G9+8RxbD4bQwSDhGA8kA4m2hjxiztDMHGIZE4U2JqCDwfUXq4AskAAEEEcYiFgmf7nVINXQPTYEPGDXcCeCJ2uCBpqpwbu34t2DDWLN00NbE9DWeOA7xoMnwNpxpwDXuE+2vCc+g5lQNJk807EmXNshi81/s9icb7E5pG8DmWIJTOEjmEMI5vF4IxgmGI4mImKBC2hiXBwazI0hEDSw0RpQrNHEeDJvBioGAVZHexDAEwYB9NARXAqiMSDuaAxgOjYKwAMBB5ByAwq7Go7GQLsHzQHp44CM6nMBOYAUYCPY/76H7VFoS7gGGqOBhJT4T5EaSI3VGhCZ0R6QzfaQzfbcwoGhz2SbV4ugxIISokPA8osIjk843laI4M5eDweFjYQMR7J50mi+FMolVMTCwY8G1kiDPwqFzRwKmxE3bGDRIL4CVBx/oqBpM9IoqAzOSENmpGFQZeRLMYFcaQT3wQrkDfAUcI6IjEKiGbxKGfGLRHyVPwTRfzxHoHhLRQAy8s38Ywaa9qcg5M9F6LMEgINA5M4zxx1sG349cSeQ4nljaDS/qqN/jaLRYBiDgijPB6USqIAODgCPCgiFNtDgKf10iPEzrH8IWAQS/idSIMoLsJEGw1Jh2E0wH20NHVDsdDR8tFEoFNgdMB46lgTQHXicAFwAazrwVouGNoHDb4Fj/AwkL3BgSiAKgwU0iNWPB0xAr0Vh3OCgrYMtAVCgYo8NgmEDYVh7GC4KxoT4+vdE/I4f8d/x0etmAkng1Xc4VMt+yxnjVxJ5cODmdzwMEcENPDd0vHjhomG4CBgIFfFnhNBr/r8ixDdjlk/xPA7w2gBoAj9TxVsxEoaLgeFWw3CWs9KCMdJA/InzO+Fm5xwCQtO5qUfTf6U2gI8BWAsGGL8zmPEPwf+Jx+DhMWbwIFLFxalT/2bXLPLO6JP4gYCeISbgzGFUwEIdKoK7FzBsCAfDhoNnfou04/dmDO1nc0ZTffG8vsU1AG0AmQDH0LS0MDQUzgLiAk+X19chYGMUnUAgcEtmOETEX31+RvQTDgPqE09IhrH5QBguEBn2S40/EDpjHZmXSQy3TmLIwBQy9+jAm4cL58+zJ0B1nl8TMKHA1FhedTbWQP4CR6HDIeL+HOEefmaU7CAlTDQcYwvN4TsHdQPe+BqQDZ7zM/MsZjbBGp6NMXykNSAiJAR/hM3jI8qSV+jx8UAH8j/+90Cgoea4mntqhHrRahTGHBwBCNwboMG9w4XwekoMIQg6H6HdQG/CMX/2pllHFrTbzJkFTAO6buDkAsFyT51QKlygVHAFGNDYuRe4hqUGkmcL5BeQ4eiguQXMCEFviOedhtFGwFg3bit24+YI9ytHYD02AYMzw+BArE1J0IkDzQbtmj3DE4icGAaMA8OSYTgGDB2Ogmwng1bryD9Po1lwNBvKiiPKBa7hikKHaoCAu/0anS3nbheuAGv4DzNnBn5NdUVhDf6OyZVzM0SKByZxCG4oHDgT6mjocVC4MA3e1gJvzDBcKAwH3nXBDuNAeeXE4yEgnCvcCO4MRcaZAGJizCOBFZy3l0D8kODUwJ24FpqINEFSf03W0oL/sfW4fIPezWal1uRXZjkzVdIEOphiAqCYcXgRxrnzTeOdvIAYOq+a8PgMzt5OvP7oBI4Z0A84ksxwGTIWC53oeSNgrjGEy73GQqUHugNE+OWKM9cVtOvf3ObueYh5rjxltOtsTRegaYK04wUBHP/N/0vQ1vHng/eEP1UMYR78ZOLcIHn4TN33AL0GmsnS0gJf6tAztIAxdwAqeZA+/o/K9eseuIuzhdvx3wO5wSGB4HiAcCMhKP6WR3vOvD+C11K0Ia9nammpU8E7I2/E5pflXCJyq8PP2gL2BrdCgwMkxuVnc12DQgfAEfG8GSSuGkDErQFF0Pk/UWcFyupfAguQIHftoOby0zqMI9zkNwRrHsIf+kCP9+L2FxL9PwAAAP//7L3ZchvLsijW53qK2PaJ8IvfW9zbErAF9WJjICmRWOuCoyBxEgcNS9JhNNANosVGN9TdIAkR8Cf4Mxz+BEf4wa/+BD/5F/zsCD84h6ru6gEk9rnn6cbZa4uorrmysrKysjKzanVjuzqfz2v16mbdaBj1o/Z65XX14Wfl24v6SG8e6c1jvXmoN9/pzfd6862h641PunmgNz4b315UN9f0+/bX75tmr7Kmu+3VTXfrteFtui9fVh/W9LiNVZpQ4Vf3u1G3MXun/e3FVkc3N9or3168jF9+e7Gi//b7txeb90bjsvLw6U3nJeVufKxtvMHQvDrHWvagQ+bBtxe1Hvx3X51Tb80m9Lb6QMFjo/GlgoMwr6HZDWjqrB3pA6NpVuCzunlmmKsVKtesQ6mGVX1oVjD3M8w+mz3DWq45csPwfl/lehtYyH7gLgCk+no4h7rNo3b9DH4vRVumA4OHnx/tHv585p/Xm+u6eVrBSk0B1Mafev0WhvHtRRfh11zFlE3zdbs3n6/r9c+V+p/Vh75e/9NoHFdW/uVr+z++/Nuzynfj5cz4+x/f4H+G8fev/0KB7zP8uXv55rffjJcrVSiOI3zABjdp/nq6GemNE6W1CjYA0BATzBkO0wwMVBqxkuFIb5zqjXO9caGfGElm7K/ZxQZx7DRyhgoN84N+neZkQNJcYYlNORONM4hzqg9O25nNBkbDgh5GunlSqb4yP/9eX+XscwAnxwJM9wngzYpjNJ1222zwhMHMtdttxhCetwvDtHEcOiebpkATU8Q/UB/gt1m5fNbef/58H/HAvK7KNNxTjCiwtgbgsW3btm3btu3ZY9veY9s29ti2bZtnzrm5Sb+XJk3atM3K34eWh7I9w8JbpXT3VUzSizkrlOtMm+3oCUiHvkDdq/ixI+Z8+E/YP5rp26//Kfastj/1301D0JTds2Ziy5ieSGNIvXLzQf0LONu8wWtxFIZBxn5k0MySAbAMQsNf0ZsBl1y905zJf7syIrX7kre1vmlnDG5P9dSJBRaK+nB68xSktVWrdiIJrisgsHVpeNOS5Nttx66N6twsNkgwBvWa/fzV0N0ruQpPXSboDGkBVYc1w57E+vDZ7qldbpQOGFY2a0OEtARfLzgKxnoBCzDfsd30aDYzmrfV18b4Fxu1BuQgsza/GDYrOeb3MhKTITXOsJ/QW1k/aRk3q3oxZj4FfmRcgV+nXIzInWpvT+JOmrWqcWDLfPpegvF5eyCbm3Uq8re5DpxlIMt2eaANKc9kvCHPZIbI8UB+ZRyI+ie619iDu8fbDE1XsUcYlxm6XYjZzTxtekTGaFoa5xzojwjLhZ0bsYf22uGPP/JO4HK6rbh9ruK2yXFECVfCawqdRt9sToEt05riaKzaMbh5r/TcB14YsGGH9VdbcxuCzOGwtgiVnXDU5T/PsTYxOwVK8mB3sC3yQ3/2nDzbmyUg+7kURhxdOWDjWx7OFbE7HSiPtOr+/GGDK2gzFzy+mP0rFIHwZ+/y7ZnDXzAC6kV3pDH/Sthm/e+gMGAjDkxhRmbs9XoEvwxBObKec6Mjgkc9NxpxUO7EbHa/gY5fZv65puKkpqFLgnEuWAJ2Z6sceaDe3OTQtA8PMIYoQJPvpqjFmqAfU6CYZSCZ4nyxiU6YFHQPayAmLvceAYR4Z8ODJCYIeNPuKyILmDCWsDScCiRl6/TYWY+rtKyYIT/uG6gAH4iKYxmygv06/xyF/FAMMy9sNsQFtBB6h4knejAOh9VaCswfDrxJlV540xoIegN/w+ip/mjtlWnT0zkVg++ekN21Vp2ZenqASXQAM3KYoFsIKWG9PsqVzGA4dRX8nRmEZ3/p2KwThWg2XAyBgRgjkIhTUXCsjWYjazZ/VEek62C4qvBWKN/BhXrmxmGG7ufp2ZBwPtM15Lp6XABphmxZA7YZ8oP6E7NQ6AviyFjHwKwNDMZW5JF8aGg4NVyZA1cMGW8vNpfNC0JSeYCkT+KRXBdj8yZhhlBBjvpIJfRwen0ue3k5s4NKAOZpIZ1hzTbXF2ELtr9XRko79x+xI40VJs6XV2c2JHln7weQRNzfkwWGDuIcYKdY9sLyQ00PUFvgIkG+ZlYFlH70t4ZuJoDddSSRuZw+4PFT2/0pWxq6ukP5eELfzlpNOuwxaOcBpG6aUDLtOMLml4QxjlcKgyLxykRkk+PBDMAVRDaIGv4mhIQAGTnuRFkmAlEZVfSCBCKRzmLJ/YPczr5yBh0ZSMj9SuaiBhYsbj74fVU1/pSz2tjDok/ZJQQgiThyor1xQWujHb0IJPKLTqwBTwzR4jmjh0g9JQzwn85Fu9zCE72h8q6CCnNng6DneLKmJ0YD/gkX5FcU1glSGngyGQQlm6edkigT7QFDkf8cUjjfOB0NQyZIM4BtgJKx0VM7WP9qOto8hXm1trlgnH6o8Yu9G73VsWTNcZA1GY+6fS0wtIkFJz51zrHBkBeLnYxPEm+5AKJWlUvhekbON4PxwsgdXfcdZI1R1sUifmwLVWgcmUoT4IUKRrPQDYp6wdX5e+L0szB7Shg6273VpVzD4FpIlMvJFU9Rdx5sIMkuXiWQE3eqkLKgNhFq5flG0UjE1oTnKIi2Zc9MshIk5HARZXjhcAGTX8N3SgQGKHG+kTJdcPpAn6NAT8CXSWoM5SyEHSrXJ82AGTL8ze6j6OicrTT5WFNtIQrhiK2lWRUnfo2hix+fZxqmnS72cdyd2I4NoBkYd7yWB5vlNpAg0shXCIAGuP6suy4XzWSbzwZIRzvlU+wlnggDDBnbLsrrR/3HRfjzQW4uzox/ioxorRGRq4MtoQEdgbobTPAy95w8/9UHDgRnAfAvJuhu8lw0IExEl4DAQSYoHRFETRtlr89r+mkQPRmDgKsBYPfVspMt0cJrn0Fo9hrlta55oOwAAGwNXsx4JoDnQJIlCxaR112Uu5XuVsOHPhxH8Lrdt6rghlONYoVTWCLAZ/fFX2V31g2KZjNuzELmg+kqSY6GOiM6vxTjZL4H/MHS85oenOK7GltGZT54IcwG647XXS0YI7RzFSOcCAZ1ONAi6BLYFhKgRxPA2vxQidEKuAUyKzTDdEOEDi5AjUNC4wvAE7X9x+z4eKCj5CxA4hJGhruuQY+ACwUm3jwbFwA2DmO466uPj3Xi6evQJZW0iXCh3YLtDrG21gejVbYoJXU9WsM0itPxlBHNbFjU92rXpq8UiB2b06DAjiOo52EsJoy8xznHWE13MynBgcgxuEfui0+BAB8gZ+OuvtxkZKzFN7ZxLFcSrr7W9ECkhyjpD5UECJCc2jhqF4PFlprepJ6KdWVzmGfze9rP647F+s9D7w9+79dX7k8DcnRpE8KjVG/Firq6/opLnme+c6m7EH5qfL47j3wpTUKsBRJQqYGB4Mac4Q7g8FL9EySdB25oJb5orRz8k7Ccx8OMH+bw3euUfe/en9hAyVX3aIKub1mUaF9s0drhnACvU/6fo5tewqeyUWZlU51Gq6912anyNQ8V+f2PJXA+WtV37WV8amr7LCjGG13+mke/xoql8wmp4p3rnzi1pxexi7gHDMrMgEF4t30Ebr2z3qremp4zbMe+8pRhLBxV9i3Bo7Uo9FADQ6rerwl7VrlaNfxrgx//wFo91avaW+2v7Z639R++TEOPh5Iv1rMc4s5S4eGbh5tMqRXTeejk3K50++eN42Nv5mosLv9mtZErx3loDuEz8+mn7a82oKE/9HpGUfSUGl6OsI1SpGyimQdTnkdD4+BfX+NmE6/zvhA7NgKVwF8lbFVbKzynZ9TOjXpvhjqJu/uFvvm5CZcFTjU3Kmrfi9T66vrd398Gy8f6kuvC+pXNnq7FkYlV+MOl541uH85PeyU+GmuM32YDjm167W/d3Xo+GC3aYq0N93bFHZwssevUvb6dfkuaa5dnwgcoUN0+394WOMbXtBz1PwxkjyMMhkI3Gwjv71egKa/P+9wud99vD17/gstvznwoFphkWt93BaGP6xqMnvNg4eUPqDeo/UkZwFtD1yo8HDxqN7E2GNr40rJmvN63usyWAREW1jEMERdr2IHLRqtlKjNXNApVMdV7a3x3WNjxamJyr/peOdlXHMjqbboDHQGqWiHK+hhWNg6mrP9526abHXV0RFTv9mrByGqsCgRRtdbRx5wL/7uN4UVBYu3pTp+xBpc/dKJQb+JY4TvuKNEpHHFWxHMGyLjUQj7xmIKg9p+wHi4zMt4mCyV+zZhxp0wejqVw0+OmpPTJO4xKmnesf/ROOiTBJouU3AS06WsVKCTm4AGRGHPbY+aUGRHOKy4fBHmYdyMkISZpBJhGmnbGSyV+i6SichDj5csNxzX3gpIJs9/qWEFrqNvqjvPoI72GnJHvVObI6PQhDDLUoxxdlKhu3B2OmTbNZQwjhjbG8PSGiDXAFuOjJEoNAqWSbJ5FhoaXMaJ28EEBU2izD2nZ7dg/ax/dbg/56hcyhKP3RoMuByLoN9gVEPmQCNwDODiM6xO8AV+E/Aez5TupFOtDX2fEx9WpiO7hOvFvqyyuq64Mtq0gAjkHbNZ0Xdh8Fhr+dTx+UEwXiRdwBCCIiAK3/YshHGi3wqH3Ssf4H8nyQML1LkLcdKeXQ5f7O6Ybzsuh9mFtMAKkphif7y5EAvhBLV+9MYmU4LRagghqOz8VomR5+gExzpWyfeAJGiVxYf64JImbIkBMxgWOsnJLmNr3/Y3Xqd+y12nnb2KStq19N1Blg3H2751hi946B/4MgCUK5h0N5KVg2Aaq/xf89reHGMnBuYFKwW2EA7Cgh30ngKfO0UalR6UyMx6Tz70iUwCv3qlLqM8aC4Z38uTWGEfoAH0prGTOSh/DuAuFYZjk3bdaeBOHTzasZ8Wlcc1uHnVhArUvISVN9oD40A/2Lv2qcNQVPENLrFbIs4IeO9P6XUXsq0Wp89+3XKtaJTzOBzKYMRuFh3Z7paz+lmIKrJWnaouNEJjmEdkTjNO/nb+QMoDHl1FZunOLreh+ovWdqmffsUrvK+8BcoXVDnNLWugMEFQFA2wo14tgGr69PmpnfQAb1PQzVMBVAssv4IviroRluzsTKSfU9C8nvfM3/LdesehG1ZFBS6ywpVcCwEHPBtssPF1iOgtfLVrELLtRWvzQBK/0sl1gHQEzMx7Nr1dDzpMeyZv82xj8R1/GIBZXvqXr6y4TivbqRFU38JE7oQFiS+zHV8eOdHyBYtsGGB3gk1O6RwBePlqMF0vrlkcYakc4HZ8B9LXzJYyNFjiEB4amcp1XDB2zJwAv+yWI5BKHiNHkOqhi3v4Awz5Izi0ARDxTHCC9UAZ6CzsnJ88+dDtekyMe0j6ngsAnTMLwgQ+yf50Gg6Xn2qagx0pcQSamP1V96mIgaaotilu0tg4dskLl1ayozU5i7OxqRxe9ZEBtGtqtnKFcXyDtV9afejP5/R0kHi+MmX10LIZnqlvaQ63nHtdRgLP9wJt1L44Vfh5ieu4TjRDRL9lc24ki/KdW5tkYKhBe53rCCL297oDz7/8xjChslUKB+rWof+v0C6zqMYpTQyEBsg7xSYhgRXKFaozMMvgcfgba0xNsWirr/bV6xSnKDZpyR5Xway9ozW+ND7aNpfp3/pnT8Rb07iC8ojGYnVFZOZozlQ6cNI+RvGxeUzdYnGww4p+RxJQLeegCTrErkBDQdT6uo1i/ilVLJdaYi8w1vp/qYNVuCNLJ+a0a8ppsuhHgK5KtsYcwJEf88kxTePCZBbCwRJgPrJ6FeCqehHcrQJKb7+yy0jPylxJI7kEXB+ZBc9DMwa0j+67oMI5uJj7kCrwPWrE3Avcc9NmFralgbxTKfhAVu+/gb5sCJ1Qwud5S3WpE+3TEjYiP9SUKfQ1OL7zX5ZGmu1k+DFxxsM/RfVAtPJIjBdSRMDopSn8wNRck4QgrsBjgqw2K7oyc/DR93SingyCH0rukgVADY6KRZkT8cTdzsR2hhuKl8+5gGA8oDcphTX5TkkdDMipsV8YJkMjmXI9/WLr5+aE4tUvExJREsIpBoQHwK9KlJ85kILfBsBspW3rlUwkKIrlSEbVJT0QjKk5x/Hs0ThlfQvxOwqPC5sVuxkAgZyJyXzQ15MMfwfBAGYxryXAlzTX2fjE9yKq0TQ6mRNOu/Z+P/R3PoZ8qz6FmqX8WQOjqL7eXWyJ0Nd//ysJC27d8dRnJ2zaWdtSrtODL/gwBucEX+J4ee1fPI+PXTr7B+7huM/3lp356qUtS0dLXHr5NectmboJ5gHCH/1rhGSyoFOjOpyz0haNVwf98ljI1ZS57HBIzGh5WuCRCRXeN/Eyrc198tKc/9vkqsx0eNalSPT8YV0QVxX7STbbFEYRYKozVm7/hWVyhEmeowZZ7//OgGzHYr2Sz9c/CYnd0NUw3RKtigOxJ+KU9Lm12yFhpwwM8f4b1AUT85y8L56RapqDqDcZTdyTmwWyuIZxBox01O2ujagii8Jrihrc9y79ITyOWoHOywc2mKVXTySdFruN3CLBwb1YVkDdfW7YRZ3+3LzLlm6yA1yeMYetrH6873AzB6NfnAkxAnNheZb8L3b/LLNiXgynv3HLl06KQztyUiqM9sI5M+sypb2jRP1gp6jrdnAJTKQdpPBOSpdbxEjygAAQW5uuKhogSGovAJlDJhA/JBtjsGrL3R6Y9HRm17hm1QZMrG5MrXm+u9AaWWaP+nkGXE6XqU8YCcNEWLiKDEdGvgIgxG+qu6iIs8I5fMpBfN3U5qXepfv7ZzKW3G7cEI7nN8hxn8RYwrQyw0IsfKPCjQSExx7Xj/3LtCY6nSjkb+BQeyacAAzoL2W+e3rW3Nlcylbvbp84F3VGpIqlr3wGsG30j3o1vPyKkgPie1qXgrBq3mb+r+nPlNyW66T9WVngHdrfGI1uFNLYZsPxz+k6JgyyRmCfw9ZMdDnA0NoaHsLsd25VChrR77X407/KEEvTwaxbPV8SI88IVsQeOIQJlB2NkLeq+1yy8g5FwbGpUEcPD+/ESkeO4PCmHhRFMUKkKGCmFFKGMUUAka51W9SwXd1iwqDNV4mcvzRNtvlmwSsLFEe9w1WObymrxW8rhJeaWqcJm986Bv0VzUChx5ORgdLkGT2W4wxYH88u+EADnHdoabF+L2gmZ1hw=
*/