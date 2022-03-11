// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_HISTORY_POLICIES_H
#define BOOST_MSM_BACK_HISTORY_POLICIES_H

#include <boost/mpl/contains.hpp>

namespace boost { namespace msm { namespace back
{

// policy classes

// Default: no history used
template <int NumberOfRegions>
class NoHistoryImpl
{
public:
    NoHistoryImpl(){}
    ~NoHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }
    void history_exit(int* const )
    {
        // ignore
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const& )
    {
        // always come back to the original state
        return m_initialStates;
    }
    NoHistoryImpl<NumberOfRegions>& operator=(NoHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }
    // this policy deletes all waiting deferred events
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return false;
    }
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }
private:
    int m_initialStates[NumberOfRegions];
};

// not UML standard. Always activates history, no matter which event generated the transition
template <int NumberOfRegions>
class AlwaysHistoryImpl
{
public:
    AlwaysHistoryImpl(){}
    ~AlwaysHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }
    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = current_states[i];
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const& )
    {
        // always load back the last active state
        return m_initialStates;
    }
    AlwaysHistoryImpl<NumberOfRegions>& operator=(AlwaysHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }
    // the history policy keeps all deferred events until next reentry
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return true;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }
private:
    int m_initialStates[NumberOfRegions];
};

// UML Shallow history. For deep history, just use this policy for all the contained state machines
template <class Events,int NumberOfRegions>
class ShallowHistoryImpl
{
public:
    ShallowHistoryImpl(){}
    ~ShallowHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
        {
            m_currentStates[i] = initial_states[i];
            m_initialStates[i] = initial_states[i];
        }
    }
    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_currentStates[i] = current_states[i];
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const&)
    {
        if ( ::boost::mpl::contains<Events,Event>::value)
        {
            return m_currentStates;
        }
        // not one of our events, no history
        return m_initialStates;
    }
    ShallowHistoryImpl<Events,NumberOfRegions>& operator=(ShallowHistoryImpl<Events,NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
             m_currentStates[i] = rhs.m_currentStates[i];
         }
         return *this;
    }
    // the history policy keeps deferred events until next reentry if coming from our history event
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return ::boost::mpl::contains<Events,Event>::value;
    }
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
        ar & m_currentStates;
    }
private:
    int m_initialStates[NumberOfRegions];
    int m_currentStates[NumberOfRegions];
};

struct NoHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef NoHistoryImpl<NumberOfRegions> type;
    };
};
struct AlwaysHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef AlwaysHistoryImpl<NumberOfRegions> type;
    };
};
template <class Events>
struct ShallowHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef ShallowHistoryImpl<Events,NumberOfRegions> type;
    };
};
} } }//boost::msm::back
#endif //BOOST_MSM_BACK_HISTORY_POLICIES_H

/* history_policies.hpp
5TpPpUNYk5BiXoAAXtW3FiFeaJ8p1HeMoJhvlvdVho+UPTPMooeTmOZKbSGF+m+b+lHJi4gx0HgUY8KNYR5LS6e3N3XAaQfNpPOj8EdixuliMVldy1CplFgULxd29nzNts0N2hba2J8iG7iOdburkOWd/8fqZKy/jnDTVSG9bbU3gdSkbuB6AXHl+9TEZljurgOujEhsnAfgzcDMiPE2Yswbs3EA56kAwh6VEHk2cxEOaG3MIMu4OXSbgb4F+Qescg8+mxU+dU1zLomffkKnh9kPh06AxJVf7oFmoJ4OzyO1w0+cyBdcc2Pwz3IFlFcJpCi3kYV6y7XT4ga+468oD4S5xTv9iH3N5ON2cua2TaVY7O+Glm0dA0InyhdxZyixisBG0kL066pDjx3g9HEu7Of37F8uwIxJGQ2gXcSBk4AW5fN8k2CMd/xbXL6xp7aYuurnFKQcOw3V3ksoU5A53mQOnEBtqxThZOPWY0x3sSpw0mAtGo+swaFOripQ4TjEyopgO6quE6VG+aHCuk8YTO8VNQ+9tm1M5x8VMrlkaRiUd28LtUCbAMMrcHmOZk3tqGejIQlfZJtbGq9z28gco158VpKCZ8tynXEu9ekh2BrkCLcc3pvSHxIrvPGkWTbk+N+Prn/+WMviT/j+upqnLJJS+YraUJFLdlQP2JFnyJFLLCRDYnI6XBdQIU1vrzbLVajjHyFBw+FjF5K/gV/e99W6PpR2/oAPLdxJBwdJejpdUzWD7LhpTbm/FZ03Zk0EgxKQgzIMI1QE8Il/D3fjAEVy611SyI9D9f7F2rdKzXu9WQRSF3EhcLHteqXCGsnE4Y9K5xv4Ymdwiyl+l7jLSkVTdt0khk0/p6AU2JcgWxYW1lqCQDZFHbfZhKbBL9E1AAbDZgd1jUVxNNWrRT3yRtUV75IIYugopl0+JMp9vfBCvAyZy/nH1c8AAiz9033phRUe79QtHFG/1gNZwAUvMRbPT0RCDlsikMJezmP8r+mXOqaLza/afqNcCHbtd/YTN06jKNznWV0aMUwmQGdy5I6NgWYgGetertqg8fAv+QySzqdt4gKOd/ovbBWeRHXi4RVfBe6+GYfashxu0HD02EUMw/DqvZedJwGleADH2Qr09Sl136mN3j68kjmyoJZIxFMZtMpAFNM6OS2YdYKFRaNygaeSfxowH+i1E5jqZWlylIjzAz0ubaOIh1EEn83iz1mY8egmjdy7K40V8cjSBwB8p2yy2tYvchJROkKlxNCSh0Ar4It3IReV4CnX/VJEtcd2fwptKDRFfxo3UzewHgcLGzziOsUosLObN586cUqlOVW9WY9R/UMqrxi8M2PXJs1q5GO4hQQFcYVT9tgrl/687WB0cQCJohXOgaXjRxjrFYUPZFl3IaE89q8BkT2gwnM27vpUjoUALv4Wi7jb3ZQbripQVvpwO+Dmn0pP2AmfEatteHdNKUesHoXZf4hAMc/mokPCcGn0fx0OZwUBwEa39gpTVmqERHu43TD5pPQ6YkTPTFjMGHEfm/Ik56PkHvPAld3GCY0eAPxZtRNdTi/uzCH2YmmyQJkrqJF7x4VhbmrGVy0q8vJXHmbwVNkDYZdnDkHy064Pf0npyq1fcLm0vrFq9moUJGfm82B39kIrapiDWh2Wg0pX8g1wdkqNoCabM/CdF1nKKizEW2iglAGj6wJrxD4GKIJWFJ5hzbajaLOB7+bi9RYG1JafJuuvcsnYIBK6TPFYz4I/birjcR1fvyr8DLNeUw4LxR+jh9kQ6Tbk/6FT7Rqrg5Ow2qjcRwtVTbUtL8xWxAtXVfO+nwa7S/mRH3kkTlO+0VlKicjcxDEaUNA5QeWpgO++qvF4PY+YAAneg5i9SOWW58G8nbA9b/uuEhwo+U7lLZan9ELNGe1wlEdAD9Nek2T1T4MOQBlATESbT/OCSvgOp+5RINHxzXHAlV13HKSd+m89qSdqoLq5l2STqMnCrI+Ih1yU09xgMsgoDnV8FZOFp75GEZG9TMqSsb+mVIcArfpkShsBd0e3873FMxu6MHukTeaIOhc9mx5UkowEYnlgX1h4lX8NC5AYZck26QdwpoTCNs0H44osPakT/GrDgP9GLaZg+gxWFY5va2260K5DN13dREu5wgmf5uvvaxZbiKMSG9/fJlyGtorpVtSbyfKRIRfnkppS60KLp85X0hrYW5nG493ki/yuJxTsgk8ZkSFETMl7v+atzIllsBmPbalC5ml77nljHt3V8EB23W2+P8GgZeXONdIdnnAdbF7yfkbYtcbtm0XgbvT7VENh2e455u/Io3sg9iIw5z2ITVcaVJEX2DWDDGHJHCSYEUPc+OC8VC6U3WxGNW/f/8hx4plTxMenf4YZvatD+6DK99i8+jfJBUtotzAd8ddIOJa+E2TDoFe2swH4Foy4m4z5cwDxGlh/8Z1JmYg8VpPTihp6/q4OsRJmqkZRvcA60Ix8hrN8ZuMOv/5LTAmXeVoLOZPT3rVlEs8Xx/OkzYrTVSmcRxwSiJkq6wBdc+p7zRerGPoZGyBP97eHm26DZ566nGQFZKK0T/vq0iI09jgy97WfrBiaTX0c+bLFce5yLfv8xI9PamLMFv3A6ulz+MjtS+/tQi6feGKK/QItv+opORLaGdl/RDZ2EHJsFyfeg3lgg4/7doxlmfBj3emGVT4JZ1pENVcB0X5bJwL341XZE1GQXTQIUN4LcGFfwNGHQKoVCH8FcEdA4vka95tk97RRplHaZ5O0IEFSGtLCyibVOmx4fgbb4INB++igCMWEWFoAYgf1CiEoeLmYG/HBRztwHLGLvosNYtvFnXYLC9t7e918sYJB8inDs9bnA8phLfPWsaaum0b1/NQaZanhCJ6/bfp+uld12YAwn9L7LOZ3lXkQfas9rHIR/gWs7xeuYuuulcAqOWtvlFcUVSPcq22ynehPu+992Tbt70VtUJPMsiROWg2tx3CyTXMF5VZnbVyJocF0ujE6ULWRTySPxHm0DuISU/41AF7EYB+IGafeYXwcenoj+OmzUaosT4qeWCkJuBLhCoJsZAKy7KNfzjbri80HOUdvYo++OwnEoM6cJiaJZqry7y6mOwvMJbV46l+ikcdMK7E2aMr+T+KEG4u0iEbj/tF6J3C4o/CTaDQGrFsxEbcZqnZe/TFW28wg7hUgXAOyBALccT0saaFq4YuCAJ+YZwM3Z7RvOPDCrdR6e1itgr189ZdmNHL7j8+2OQ1+A5L0J+IgTmKdv98ZVzmXzpMz8iePip86v525I5kvN6KjcqLhYUwO27+PC/QIKfu6J3CeM5GoQ20seN0JvDNrN9IOPPvBxT/weBEXaYIZhI9JPHLcD3mNGl7P9U4E7Iumjq+7dU9QsVcushCyp3YergB1TvsHX2Xzrowdo8jI9MJETG4QhHnp6tX9gW1uLHOFTyXXzNUccaiHZD8iNgC6O6eD7CRqTWLmAQYVJ8F8lKu0Df4pu6IsF4QVw5Zsl1TlJ1E9Vg9xlCjaRMZydf/P4XCOB5CkkYgoFTCQU6Ke/g3c6eHGNca5yW/ZHqbqhRNbRNivpHDLk/6Cxgu8n7krjiqPUvETujg0ttKYacUT7nSG2WGSsYaU8RE4lC/fBwUKBTKUVullhZa2ltA7Qgrlo2VazaHJMv2oeuYpYD/oFc3JxKHT9izJ4xzrQTxqD/S0Iy4e0JKx8uEXBDJvL8L5IoRv9wK3R3VUWtNzzzPqXzN/0s8JzCpLAx9ujTNszgBHUSx3+YHksHQivjF0hui0nQmQ7IFIgLSEclp8RaAsM5vEl77/1OmgPwp0jKGUB4w+Ta+FhX3AbADYKMCfCSjefaow42Nk67RfyC1BPiJQLPqX9HJdNvQPdC0IdYWfLo40+xhwBzloFaALjQYcgzGWcwh0f3pm3s5E4GuUer7+GGgYMhoMauCelKy5BaB+bIC75T0//ObOOBdSqlfZPAy585hBOQl8AfvMcvf7XmQVvAbuLqIa/txjPFF66HSOdUlk34VhwGXLTUK8u6MCctEtTaUa3TxRUUY1EmC55WYZv/9wjOcWTU/53nZmKhArOKV6aZmOOgdPed0zd7u4+GV2PHKQrvW3LQhNgpcJZ8vS/4UQGBCS1o8x2f6+EtoeFEeh79LeEyeiMgjY23ou2TOpIYuHgDyjOnZi6dq349FMY6P5FG6JYo53Que5duyb6L0mXEOT+AYssy3giweB+Z7duMFdc5nN6uy1b6TnyPlmitAn8AKT5mgpvCCl61Fyd/VMlBmEarBYXtWPP1K9OPvTYNDYRKXZtKh+uyfTNiHqQjyzZdmYhVh7xKg0z3wZYF80cJ3x9zWqPjA8VeNHJ4aNaSN3OCOUiFKuu3c/Hgjln/a+f2w14wKQJtV47dPCVw4WPq4wzPHG8yyOUrMT92AWxvsFbLUB7oEHbhI/UcmnZy92bhyOf5/CV1sTlQGGDpZhvQMYLeOiGr+Lew/CcPiWENTy5eSp++o4N1Q+x49KFW+sJJa1W/e7nym5DaBVAasd+blDs8tK2p9p4Wlrzad03I2630i5gYiIZIKCIt1agVDmF0cxF+MdB69ApvVyw1VeA7Mml+J2QJemX+SOQ4bcQOri2b5peNCHgotxqHER2BiIbRk8Kq9YVv+v9wv2QALFbAnIu2LAYD5DVQm49mb0iZK1m3Y3qpZN+7mQb3rGH8tnGs0on293qWWyLDd05kKI/SvZ2ci9rscC8PLP87lcmaqJD0mqQri26b/qvbN9Batops4/j7O5pOZBbmOEXKbC2xTS+y4xFFyRjoO3Pk5PNWmV9fr8oLfr6mWajINqC0qoePxMsSMq8kM5gKfLna+5rVNmLJYiI7bj4nG7IfyoEuvuRGSO59O8zX+bPyfmXq3HRzq4VYcJZzgRJ0I66ESPfec/Z4PLMd98dede+jr41In4TE8vLpQZADaWkH0mrRj8SeyUblj21bzKrD13F87OYJtU/NqXiV9Jv6qOan6pePIQ8qVXvnyaJzTTFbQHhqRXjKa/YdsDk75wVT69m7F+56EYr6/t554IpT1Qfpj4rkeXcZUg5P21IvCLtR/ln6v7b0s1xw/an9A4Lu/cpyyT4S7NGjjW8LsZGI6c5pQryrVaMKz8TKiQvMUj2Y1xa9l0S583DLC1axD3MFftqEdfzUAxJeA6I7F0JoOsf5SExRLZAKcVIECeovmVfT7TzBKyzIS/yw90fI7Kl0ReojzHoYvBKWWPKjGHBPStwQKOMQCuC3GcPll+jXVvkrX/8nGD7h3oHYiOZKXNjlfIHdbc4Odk73W/r9L7FZQnhwRdorTk0NXwuSYEkXaR3rWHddrvlk+59StVWxeRE3N15PRm+NbYxE1zqkRMQMLKlRMNKjnSleFyMtUr98u/fpJrh3fwlvXYnGOZvgae7YF6xIC77Rh+/gHu7+Db4gQRMj+go7nroY/5e12q2VCq+VXuQ/G6+GIx4HEiSk5szsKE0vpqA/84ED1pnOqof7cIwkaR7G7gS2io9xJ56WPn7oA3I2y20IMnKZU881rIFgAOB8p2tK/mxHlDJfH5l9bBq4uz9856Db+aWrhRZJevp6277RFDYVqcoTDv8DQHnBw4yl+u8UH6BUCfzR4Oz+n5r5FkfxoVXg0PoRJgNdcCMV8HuCX+REgd6CBfuH276YCj+j0dbjKaQ8uSgkpCPWJvaTUbQ4K8MZZkyO+QgUK5pA7yvYQsiAXZPj0EVKmwfB9kE5KzUWEXUYNw5Mqz2MDcqPNT70c5eR8F7ppBUqCF1aZc882eVZCoR1/ANpqH1v2YHFeQpoZBBurjDu6tg57pN8kDD8I7uvuOdmVL2qqu6K0/S2eWZ5ROp7my8mQFN8U9OijoVyGrOfgQqpQuEoFL/p9yrACXVlBNS04VqnfHvwTpuDtdM1h9RGXED3SAXE+gbj/5etcxnL45WiyHVx+DMP4w3MR0dea3uvkXqCT6rQVgySaam5AU+0vX11Y/CPyH/SnPNUvIq2eNur9OfYEw93ZLMn96VOI+3Yrmfs1+DHi8tyo0rL+3fCC0T+uJSoMWKiS1LUbrB4PoHj8qqi3Ob4YXV80E5Gw1vpkKs4FQY6jA2XY45flqnani3yDREckLZjxn7X6ezaQatVo0x/Fh/lmsVdwFqTzsLam8VmlGAB+w1Y5yy5UcaEc5fJBkTfibYcrz92olS6/K3ht+m2pUhVr1MCk8/cAiE5aqDnPMYtLvRiLhylgVOOWQinTcPw0Awjvw71TEtk8300QL2u30aK+yx+3RovnE3yGCV97X1lPaW548QxKl4Ej4b3bj7O9BC+8X9FuJeMqyKuWbIKDJp9Ly8gt7tN+pL+C/UVnCIsPj3NCVpSvwZkL12dBMWtIStbonNInwh2N6XaXij5vD14nXG14YwacqQlN6HXjZXQkQ+vtp7fBM+RJoMz3Cw7YuPSTcXBCIagfCO1FEwQXUt6ireSq3qOghKkyQlSNSdO80K2ctH21a1vd910OWJdmKMv0tyZXJPdr4q40yw4FVlu0dTjtLcZqN15trDLx/cFhR9/vWfXQ2snEb36gtcWiFS+5n/hNRYcBmEVBdxF1XAWlTJG9nQhanrur8sPdoMnZ8PMcP6JWs/+QuDAbFfZIChTzNAb7D+gEwl0iDgjqdFCv4FZzFLTEhrlYE0ZOWpNaon4Et1YIzpbnPhcYEbQrrTYBy/4jKcom4/0zV//mQy1YvoEqwROpEpI0scsDMqbj65j7Ipjss7/2n+ozFkPTXwNdPbmYJF3jKdZvCJ5Qc60/TjExUdPVO3hbvhoyecejuYsjy/XMYgnfXLvu8BQJ4AcNfy5p/MrZuIh1Putqc+bRnedLayNQ4KzeyAX4yDrDwHXO0dUcy22c2W5rQTsHqlEpuhjMOlYL6jxKpK/4h5ZpBT5dwcVMvmzY3xa4FcafkGpSaBHGvLd0WX+3q/UeXSPcFdZDybQjULRw2gPrCLs8z8z4sZzhcdDHbz3YvhfsNbCziddUR1iQ50twBF8hJGfeIflrCcwUoOXwjtWskZVvz5zIFQh6fLmQv/9R0VeqjwYC3VHO9YJn/5R2579U1UMUBSgjln9FmKHDzAvt0Wu6/WCeXsd5wAx1FdK79N7qGdz57My5r92UbmNakFJzDnk0Ccgz/LmX/Zo8+4zGnqjpq8jfYN5h7XKro9ENevlbJ1kvR0TPgCwFHOBYe6h691bDP2FbAVdYTP/LqWl3IMHTydOwKVwbjepwo9XTCth4jjUdEmivF+ffp1QpjRvUxIEJMOfTR432d8uaQicjfx+WywsoX7tbGZ6EEP+3tBfnOKjlc0E7ouL9qQVAmNnRF+YRtHyxNAwXjTBqDhKe8Afj34HcZyRkxAFvp9VuXgrlSqHixef/OKHM38OEMuc+wXjfNBLKT5b2LOi0OQBMoPvB9jkt56PUCfvPlNw9Dm8fl/Xu8g+drt3n8fYJaWDPhCJJNclCm5OHxHttdvs4AgtTzr/aLkCOdokzbC9r846CzX8DnZSkfTo8+jm96deIOay96j2ub7WW6jtscx5cJUKBCOb+PAOksK4Hd85SgLIy3SkZUGsY7rMg/qrg1cQeSwrNmrjjnkC+h+0lCV5oluIiQZnqoUKvtyzsvMigz1Z9JsuJWqF+fdpNe1QEWJn5b6MJGLykfB7veKfMv+hSHSz+YtePYRp1sklMtPhdj5O7EQJ8GOHJQc3BN8WtbP8B7/RcnQDUoldH1t7OYVD0kiOYEitkHH07N2zPiR7drpcrrVZwmCTqwnQ1ai1jLl8GwSXmKNVN0lZRIhM5rjtLehLkO3Wekv2XPa2ioFojbfnjzvD4sT8J2MoBfQfX0pM3WB6c+bKCef+Q7Ge1QUeV3xAJ961b4ZrjZzOUAZVkZ7mGQGBO1tezAyaKbRaHEc3//EHGplP7z5SRwbRg4HpksSEU9HjL/2hyCfUWuv5i1PfnH84neQYDwzvw0fGcUSJl8qiNEP5Q33hh6YfRpEr4E7FNR1z5tor6D3/JkcCGahycfLWKsy8Df9i3zhN2u34+WG3pKUb+RDfH1Rsu5hZ9eD1kR012gqfbg3JRVAhsbdT+8rWzRhu1IwxVlglodp93KPaaxTKUM7FTKXH71RL5D5xfcPAZNJarITD+/nfd+b+e2cgdQM4Pubmw+NDzVC3Z8KUPaf9ILFvgSjSoYhLuEx2Twk/j2wHZQJuciasiQ4aYBIMV2y0wYsqwncSieXWKFtLWH3nzqcRz2YrBU0Vqx2R+rTy2mdl35T862snSr+DN994wqsMFoPziW7JOMeJyO3gUCFjG3qPhpWBdqHfJaqEcHVAr2Tr5IKfLGXsSWXTYMGjLxMRysDIKulZvj4XDoeRGg1T1uf70hqPbOIfySjq25fFA3zx1k8w7kY6ZUf2zxnk6tBUxLikTQnMxA5qBOrEYKxWP/q0XcaQZ8S9mhpus+a/iNrfjKAtcti5zNczDed6zjYU2bPgFnoRa5NXGW8QfZUPmkulvQZWryw5e8/sOVfiIMTcX1EcU/bhM04tBrFJfXKua63lrFqxYrQebYxYb3Yh1hXA8EL4+mP9ndOUx3bvCT6lk3eXanGmZOcaIEVM5ht3fkz9BDGNXZu6gbLNXOC+NnfjLSTwvKpWbyl4Jf9IsgdROkCKXQZ8m3yrrOKF9K9U8bBT2joMK48ngZyvT2U5T1hlnL6SXgltXVZjt4Sr8LeI7YQYCV7AIZtCgCqb+CGp53AAL+gfyXBHk3f54edUylwi9ptrx6hjl03LDlyuP0UYolsN9Lrnt22U169TTr6b5PN5RTXUl57Uyi3T9h0wCe+i+gLKjVMvcYPGNuO/DhoSclnzabXn0IMbzKWtMdSCwz8WP63G/XKPftr0EnMjU1NX+ORLmhiiHHB1iiQAGp4Pt3UXEML1DRSMVkzNuQTkAPwzd298wb2Xk360uxv37DSsECZ6CnyJmNB8+055qszpL9WPBlCJkRvn3i94dQDXrXEBWaia0w6ieF9NC51jsZ2KOCUSi5Tug7bVbj8V2PmLI4RjhFfBF+A2OE12FNfGH3FKw0eUR14koRc2T1+bJk2AGw8C7xKjXgGJCfw72IS7JIk0yVFXNBabqgoHUwjT+P10+zZgvprNMXy8IiPPsCur+8fVipyU23Ji5JwZOY/UzEJzo=
*/