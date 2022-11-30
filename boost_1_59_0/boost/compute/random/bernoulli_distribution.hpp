//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/literal.hpp>

namespace boost {
namespace compute {

///
/// \class bernoulli_distribution
/// \brief Produces random boolean values according to the following
/// discrete probability function with parameter p :
/// P(true/p) = p and P(false/p) = (1 - p)
///
/// The following example shows how to setup a bernoulli distribution to
/// produce random boolean values with parameter p = 0.25
///
/// \snippet test/test_bernoulli_distribution.cpp generate
///
template<class RealType = float>
class bernoulli_distribution
{
public:

    /// Creates a new bernoulli distribution
    bernoulli_distribution(RealType p = 0.5f)
        : m_p(p)
    {
    }

    /// Destroys the bernoulli_distribution object
    ~bernoulli_distribution()
    {
    }

    /// Returns the value of the parameter p
    RealType p() const
    {
        return m_p;
    }

    /// Generates bernoulli distributed booleans and stores
    /// them in the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        size_t count = detail::iterator_range_size(first, last);

        vector<uint_> tmp(count, queue.get_context());
        generator.generate(tmp.begin(), tmp.end(), queue);

        BOOST_COMPUTE_FUNCTION(bool, scale_random, (const uint_ x),
        {
            return (convert_RealType(x) / MAX_RANDOM) < PARAM;
        });

        scale_random.define("PARAM", detail::make_literal(m_p));
        scale_random.define("MAX_RANDOM", "UINT_MAX");
        scale_random.define(
            "convert_RealType", std::string("convert_") + type_name<RealType>()
        );

        transform(
            tmp.begin(), tmp.end(), first, scale_random, queue
        );
    }

private:
    RealType m_p;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

/* bernoulli_distribution.hpp
GywLEuQqYY6MZSVE1MUXCydZMtiiFUTMW9EdHfyQYFTR7AhlIIZrlbY9nYDdnZt6zU4GpJ2jRQPo+/EX/3aAdhTXDpduDw9MgGzbTAGbmWwmTAU8aRtLGzXhgjx1IAHoJ1f1TIShqPu1kTMgp+vKaDxrs23qDDxbtC5yddDkXL0FOC4Y8e8+uaIxgVKEBnzxKI86p1X29oeMCx/v3v3umw8fPH36IgX8r8JO3RxeTy/xoAQmV1b1DKdOQ33+8lFDLbOo11wmEE160CF1DoSeiaJtck8G4Zxru15CxcCarTG8+jqUd0Fv8EqDQjJ6w9qbD8WrYEKa9upvLmcslz3A0XjdUAdKKjRGSwEMQFMMICH5A4U6jwKlVf1MYD1qkt627cU/dMCTT0kpD+DlaLIKJZy9tPIsZmmT/xKZw5AlAEGEQ8C1zV8uHHhNZPD4huLkMri0IcRLFPA2GnjuKu4CtaRApXUq7q3XlyaLbrOzOrJlA3VCFM2gKgJzLA+L5zXJ184DWONGBDs493wGE4In58zcG1nsHIMg6vTFazaiXaiOZrZUZuGJK2LYquQitiyXzGC06+wHEq06T3yPT0ke6RMv6Tk6LyAu5PbkLK/F9ULfXwdxvxHi1jWqEXzE73eIX7595DUatwrnuABn/rDHcnywrMix74mHZoFNL3XEJwDALTHWdaEfsEUtH4Q/AVUiMAVDJRYufCxJ2xtXGIrENzFYCDGZGfNcyJC3i1Hwo3Lw4BhQBoS20UFeLHYNoceqLSRpI2AIOp3ntM3eNOO6F9eAYL+CIMA4oli/qSKtkDSB/Cve0Lhsdv/4ky9FA+KZAoNTV3RuBOz6ZcEoxRJdqshCGyrJmHandpK7qDBFf4nxjzzx9Sao05sT+PFa770EAgdaWCz9TBrpmdTyVW4DUd3tcOto5Yn49o3jTQzwpzuTh5378A9dibSYIS30fvCE8R255CNi5KGlfAlGw9omh1CuKI8GDE7jd8kATB06zcpsLFcOeDGBIOqwxNd2ym/HitbCNeKpDK6qtxxN4TWI/v9lcqUC8Cxm+ChGgr5+/4ZXM5kMGpfi+wxFTCiE+8wr2HZXibg+7z6bMmPuNZXwiFjQ2Oa3j63TRfUoHFt8HsBpIy1knM7fdKY2g4ZNnHpwtCyINSCj1R6/0QCMlCLws8rrdca7QMxACwzfdajRdAaxQtlTA7nwGMk6i3xIenKWcx36MPzaA5IrMnktZrA7eGBnypKyYMQpfmUmpwFn4mz0h4696eH3SNh4jYZ8bW5UkI5etu9BOj4x6IIqaMXiXBs2NcOwBYFym2TtSRz1VlcLOI0c4gDTSEXb5AOQdnUSfoFHYh5Yr9k2qsKWYKW681YFS+Yjrg2U63NVEF6Zigva3B9VQxK9q4SsuQ5tiaySl+7oeL4Owwb+ndpQhN9Rp9m/IyqFL1nXhJqHLnJoAzyfPsrks6fOgG6ZC0w49cKOorKzA5qmF3L7UX71yru+MXYkLJFIMBPtG1M+ezESEAhGC9+L5qyJwm8h89Yu57+Oafb5LwRFPRMg7n2uvWQAp5mXRCy8w8k5tAZxhNmyrobVa/ZoSGCAQV8FdZbz6+r2Ij2FJ7l4SiMDI4dyYUhh5mPpr3f0XR2WevVozsHEfzI4eHJdeG0T3Pt3vws/RD+8inaUOTo/6iF9+USMj3pq4VjPXEcBFglZVB3Eer+boEaY/yrbLQZCEFRHRodySzKiRz0vCsozzpjMZHbaUjEPTYCCelVY5jQBrN2BEV52khHf42iec/1WUWwOhNGwLU9TUaJaj163d69TAlrQ8XDEtdMUThnX2cj2qDzawC/obQHXxruP1+hUycfojc/qkByUYY23hJUhHaWlXbQVcgjYbIW9fKcajRee+n4HgUTTB+lebGpbvwv295Nrsjx9++T9ElYBW3Y3KDv2HRokW+fnjdf+QN5WEhndWuLiqe88MlJ96mxk0+VOv3r/IMo5p4YWR9BMJ6+XOKEa9xYA8hJAxzot0/lTZr1qUUZ1ixv2rNB09IAcoPSJ9kwqbvBGRV5LVKE0njeKLQaCsku/r8RoaErTE4AfTqWu39NKMo0vHPQHHn7JAi3r62SgqQ7Jlg7gUdfIgsypjac31ZuNXaBINn6p3ikffNyNPuwKUAxXfulQ1XRkkhcEb6BLu4RyOgVve3Llq746UZSPTfrKhy4GqUU+j2IdW98gEIem8bJepIMHsrqovUmzafWm4cqZzYC1E3kwknZk7DSNFpu0r1snkn/AP8uXssk+YYBJKHYcysKSH9sbQ5MhkbFZXqJONG3k3hzunP0j5rQb5yZVI7z2gsj0SciOD0vZ/qLwo8QuuWt3i4nFs4Znv3nqRq7T7o3mt/w6FzMrFjSuzkiEnHz49LtKIFPB2x4J76NQLqsLi8/ZwHd4ERelzSfSSioxu0uwnhgwBRPH1wgScrRyppSVdI4Ohop8PSPE++O0YrLdslQWcwLr3IRTg8cxtGIoX6latsIoF+usrTMwdhwtDbTDRtEKKqGoaxpopwCAnYF1fBBdvMuEr897pp5bPNCBx6GI1FQtEVYvrqc5/kxhJjZWcPQKVorKDpz8PIZLKis7AZPvpWWDMrJla/aWaIZvI/83AajLZtDJjfadyNkXYtWBeoP8wsRUEAjWURbR61ymiLJpU22GjcQ9/KmqfjXqgg2gE2yNAii3/IS1g0afaNFmM/odV1ONXUeiOvFGE0DxTSSBE4CdJrfYdvyrfM061vJ3Pp++8bs+T4+fO11iOe1aYjkP3aohP836B+pJHg35rfta92rapERcBdGgaOeh5X7PqxME3IOsnfWBEYwahDau3AOE0BZ97RSQpzx6FOgqeGdkc56QauzDTewwmr1XzkkOaZGEVlZ2rD8s0sj5O+0c+DCjjx3qrWB+4bbYUVcySKBzDFM/p9Wmm05364KYdvXyXFEX5L49C2FVXPEP/3UU1N7kUGlVoGzUWt5fx0va9qZ77FUz8FMfot0NNraDstFjZSmJOZBFshpMwGqr5ABGHwBRu4Evv2Tlw+MlCVEC6TXQ654XEY031RE3JqBT8hAjzjjwc4/CQYf/5xKD6YI4xZa4wrtSKk95zf9DXsJLf7pJcSPQoZ28dnyca1I/LNSrq/7TPvlPWJOX/XRihx26frTuoNpGx+yrYh7lpR5I8MULqhC63gKxxOpaa1+Q3OuMmR59IOEYuSy+qAaBetaox6eUBcXlPe64mwDRDnd/73H5hBGPxzZV3HLfDGFvq3CNWOfaACaPi1V9ZDga1iq6DsDeqKH+qKwT9rUBbzRf6yibyaGO0te4671wiFCLomA4BVSZkJNeasEx/Qzq+x6O9YxQUTBgDUJ5K5dwbo9EI2AJLP3A5olB45I2qGx6b9crBo/BuuucO1rd2yKwQR4RQpFt5zdWpFNgDITGRMtGNHQe0mFsoidVBIdUkwQPjAyacZgMjQbrPGqHvvZH1QTRVgU/uMqmbSQjDc871ArqwHmLU+fUNm1ufSNQNHds3XwoFAU4qkbDpDtJ2yKOcybOTTiBjEE7DETY+ZmmlUi4A6/lC22xaa2EJyKaP+wjuvSExwKFYfpa/4uSbK9+/tw1lyG7N+KO0SYQCvUCy7uZWpH/HpVyTc0HdrleMIHNgQdRAABAAElEQVTuJkZZfvY6pvtfnBNCok8JlecWlM41low9DSBP/FWQCeJLM7FNznGsLJjPAoFKKGIPI7LX5PIQptsKIlJ8yt4fd3OvkRbYJAQn0nBJv4TAaT7bGw/rkdaEsTQN8KstPIplYnUjV+yxaC+MA7HOVQyCpe9KQduvzI8fgZsdcKZgyjM5DFI2es0t7dMAjollwiaH8iowxX2JwUcJySgPQraSnoSjf3BUw+mOAVG7RCjSedBEfjueAvO00ZotHbGVIxyngNKdaYSMiDKuU1qj/ssUnD7KUA+O8jqSbeRQNksyYtcSFUaeg5atrqyavTpxOLh69NQ9VXdlUL2Nx9rFIVZFuXElrnppy2uby0N/WG5HeGCgKOeV6/57/tzy7iNPFa701DuHJlnDPFgbRdauk3Xie79k+J7l7zevPymMgtUpS4jNH0VRmB5/IoxMOou4gtRtYyavjhz9umB0mlDQBZohei8Fknot5ijtFFHrbl0EeCqbKqExYkia4gTJZPS6CN5a1qKcBv5OTsI4glpj0PvG+gJPIGNi3gJdHS0aVplyRDUEosGYoUH60svk+CE+57jOZUUKMHtIRqfFEbnu3N3pyEY6eY2PQBf+rv41UiqYNgFHeTw2eB/BA89UtpHjgiS9Dm0qL72SABvdxHwkVHIrpfQxB4KYNMJBxcqIeVScUNeUTUEowpt0ipoQfmp76hVLmSYX8P6LJo/uMS7ZlE2Yue8kLLjBShZE6es/64Qfrc0kPK0joC1bEXWWEi7DjZb+bLocrd0qkM7sOxwZOcLyThe04jnW7KB+SgAsWyq82IuJhKxM/af//f9MOTRx2veORY19GxMIpVxhBrcfQ+CuPxp5k/jVf2Ze+J+E2bKwxiOof8dgxu2zRy8pG2hvqHYhjjD2Oyt+jyqHvP7PJCfkJu6xU1z7DpiSU1nPz6HLKGe6RgvDDHLhPPPsH1T5XU+KYJDztEHTIWToEaimmxKEDkbu2gbD22ZV59zs5vgxpzQoLL4wx2Rd8OBwfIUTSEuf2s++wXVk4/HNKhcsO76fAFFuIN3YNTDX69IuyMDYaWenMfwRrHZoHmub7WwHXqvYzugqbe2lBpHq48o2v1Rl7wXE1VW8+cZAE45WAHWX8LYV0JzUzt52mc9aHCFMfKnPZhKhlMTZVKRDj3N1cdpZp6ki0oPPgx4wJtttsgv0/pZ8mykID5IY8nipy4itfbppKDiKG6POBiYdeMl3NLKyFqjOjsIfuzdfs7NkKbHf4fn88Y8fTreXDo5a31wtpNkl+n0N5YxEZ67qw05ic6Or67W+ss7oZM+jSE7d7rXZ86uyNTTS+M8IxBJ9NDK3X6zH8E47vNZo1PEJegzrgsjtFR+Jpl0qjprpTHK8/sqMbcrTOzvNM3nudFSnISG+UjNZd53WERKXiF2HFbAEJQLd4JIV1a3mYSQj1g6zjnyLE9A8ll2HIgJV1J140ldt0gpRax8c66AfjnUeO7URV1jPxZdgU0NgCjABDo1ocjyrDh5oUCQo2AAlY7G6QkV1p6FgEgWGB/UEtCF4+LcfgehD6AZhApl4h/yIOwIpi5VESAnDiecpZke4TqsvVaqz8rABik6DvbxMMHGdyQTvqbQoXmd3KI90WsPaTaadJw/wh302vr5yJNuMJrkdUept5ass6vqZ2drtJHTdL8sRByFfv/7ZYLtFRd28rnLbCuHa+aZxeIYoOCSXmjrFOTWtIjI1A8/o2IW5MMbkeX/eWQ/fXXGaeP25lvRJCu1hc0O6TWyWDMqJijQF1UjA+ftUQCmTupoxBJ6GpZ5jRzGLD/p2LUEnYKIl17GmASnnXkPGA7Co0qCGHLEjcF3Zi17E/PCcUlJoO2TTUY7QOlxh/CuXgVN+acyZTn1CX+Jw3KlyCMOZDhTmTkGXtNcao6eQ98ZySadQ/svLDTnEUJb17JPJgJX2tiWRXOWpfN1WOAq7a8qquA/2B05CIGz6Li+IAu/IoyIGsh2jx/VG2L16bUO1HYL1wsVbBtAUrE5T2YGzzaaCOcWOXhyvA9yIrT7NuEDykmA8Dn3aovOsREeQ7ZkA97Kx2GFqd1WpTvsdGWyvc1AeACyQ/rvFZn/m5MN7f92EJfmX23tecaSit9xVQ88/9yL3p498N7Ze6QUYdG5SaaQ91tRI4qoFEsnUlUMejZp4zCLFh3mKqYeJIKz+W0jMUY1kYDspowsABBIs3Mz4zjPHUxlnLGQxwgWzkr1TSDctxnUkcdtjoz6zH0pCOQcueBbgMAtX/GRSrlNn4kRb+hSPnSrlNfmexvTCUcJ7nWwASM9L0niGPBt0WPJsKhRc/B6Q2QopBa0YAFOA4GoY16IUKk20koZTe1/51wEYOMLoF44tdg4Fk/ZXD0r+oN5SQqgHSaTl6ok4p2aBB4z4Bv7zCEA78FI4U/p854zFSuXOlRwrG1RXQaUSxEd7SVeZ+FdOO1qvjzy+iSzvjfDWwU8ZoWHxgQF53ZJG8BPuFuALL2NJmc6zD3XKUlIPOwatW6dBEEYHAu7vcfQ+fvv0MwYfS0egDUJnj2S9O8M38/4eGH9Zkjp+hun963ef/Bq95ymGML6ZV8VMqiuxxlR4RzMZy+jta14rwCjXM2HcNDNR3jAV7PthAC1QEOSFJVTEgEwhNZfS/MUhRn7nb+CBGVGu6UwgCBg/Fo89TGk/4GM8uXyrdUoW6BtkgEP5AhhkY6d5np04Slhj+MBHnfO76PIIvGN+KFL26ezAw1SxVmHcklQ+TpVqoApYpV98CSyh5NK1xp17NzsFL8Ct01XKp/qubhbssDBZhFMX4Ww3IVsBpT46Mks+CMheWgCbEMK7bRIyvQ23bKPIIvKfLuDY2cRDnshhu+fCJEcJzak6oLd7GiIgGU+FVf5GSm0Drc1wTsIBYkls7QhzWbgplzX+Ftyte8yAaK/ERLOP2e1k0ln8Q8P23UKQPzY96H939+7rtx/7npaRw3DoLMfe4DzTS0B77eXjUT3jC7GR+8wL4xl7PmMI3E4Xir6wdSRQXD2xPXb0wh/r6DU0brqFbXj5Db9AyY4n7DEJydBIYg0bQ3z4gJcVemOdQC+RcarG0g3sWJRB2ddMK8sSg7L7HWBrpwXDVN8iwPIGVyFOAf7U2MUx5wqoIRHSxjSBtTrbN69cZ3emlLQhXo6zTfsVNOuGT5BvuiecAS1vgyh5wZnZZtsF2RzqlPDMpOMh/DWvEhYs1hT8SwxpKZZhssDiSHuEKw7uMqBz0bMsZqI9s/qqLWYADUSJsambwWZRRl1s2EbPfS37kBcBEZJ4HkovOsh9j22RTrKpDPSVq1lkWJNbF6iL9uAj/iq/+2xSt3oBP3lPXX6OefJg/dkd/follwmt0kilLPCPOcfa0T5e+bCLBlBE1bDNS4xZI/aPDzm3ffn68QcTyhHm/e/soj1uRzU9oInGw7vvZciw1uNSLMfzzWU6GZ7wkIzMEMpAvvcGNNayfkHUD+chlYEr9e5ZITQVPEr1hq9t+pS8hToTPENxjcQLODV+SkGzi32VLF8hReqZu4B8Fsb7WQWHbDgvoeTI1jK0x6VJtiwRCgRl0em1hYwUzt+PwySBczWqPWgJAK1pM/nkqyzO2wt8WVHE0zay6NgpDfaKlsECEeP+2t1gVXadehMt+eUvHvXKbGDL/yafCXMEqm5TmNLjCKK5pOleweRrwCjY2pSpE84tj5EKgewQ5ldsgJ17AQww4qv7pQNSDFBpMkpcpgdW+Vfcz3bqtbO1KJdlsLRIEtkc2aIFPclMj+EcajuRJTTsJNKZWs/ujEH/ZHQBKJNdPkBhRwcV92Id8whGkSmojMDZYpW/8fn5bz967wqujE7EE8W9va9BvhUx2pjGVREEMHz5jodNP2YDRiSccN6wxMSMVRJHH5inLxmuONQQFMChYB2QpOzcSRkTY15HGaemOZ1+wWmARUPhUpoWwJpk
*/