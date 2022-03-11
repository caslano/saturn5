/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0841)
#define FUSION_REPLACE_08182005_0841

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_helper;

    template <>
    struct replacer_helper<false>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, T const&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_helper<true>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, T const& old_value, T const& new_value)
        {
            return (x == old_value) ? new_value : x;
        }
    };

    template <typename T>
    struct replacer
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer(T const& in_old_value, T const& in_new_value)
            : old_value(in_old_value), new_value(in_new_value) {}

        template<typename Sig>
        struct result;

        template <typename U1, typename U2>
        struct result<replacer<U1>(U2)>
        {
            typedef typename remove_reference<U2>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer(U)>::type
        operator()(U const& x) const
        {
            return replacer_helper<is_convertible<T, U>::value>::
                call(x, old_value, new_value);
        }

        T old_value;
        T new_value;
    };
}}}

#endif


/* replace.hpp
1ZMn2pyHEKnV83/t1JmNiUAuJZpPrwhumfzRx9lkP956vkjhbRAUuOjnIfLpus709D3e2GZ/ftYKTTINTyFFIvUOywothgieGyPTf41n1EsjdTdr8MPdU5fC5lj53Q6KPD0iL+GrvMdSBlgwFFVmLNByVApbn36yTVE2kGWenOQ6YeUwOj1ZMVgnryK5IYRkPDh31FEkxXdHFvYn0lgF2IztGvZQz5E6Z3H5LvKpSL6y9GV8zzFoGMAE8BuazWp4Ju+ITb/oO0uazZ7FFMOxd18kGqve+YPNNSpDOUK5wIqG7YtA+HiH9Sghwie6NDUmvYby4fFPxaQCxH493bWWnzJ7RtPKwz0uyRFbRmmImdEohv+YyKRG/rgBYyzMQ23kqphIG9/CDd1AGWAyyjjgAHu5LerB5DVVwWIbeD+0tztTIaouDVcov8t8cINGLjvZ6YxMKqz3gc4FoVjvuR5fYxt/Fz5jY6px4IAxm8izINZVfy5FEK/ymWtF98ZnW8V03hzIYeFeSUp8CWRMWEqk26jHmAt/R+LgeHpJqPVtvO3fQybJ17OFPo9sDsde6KavdtV4iMVl191GqCDhDwP3YhK4plcwF7ZHFvUOukmSzwZWudOEjvYosZlgILzaAH/r/SGQdOlYMr+WVZBriwCM+M/LLlIXOZI1dizBDHqFKbpW9qH9y4HPp26BeTetipWpSXkmrEF6DftE1+Z+6FFB6lDIFMvdIbo16Hdvh1b9rUWgK8FPasSkC8wAMxaxv3aD/Di2eRgCevArJfi+N9apW2cbbIeB9RcTcgRKlRtcJBo32ikQapsWGzjYQzyx4iQMda8wQCb6T9xMjLKAaHWwwBfX8e7saWTvb10UxgiTyWGrniHiCsg2fX+jGGJJ5wmNQE0tG7acnYoRqVCKuUBJVnEwgXxLySNPX4DhJTG0ln0iq5KM8vfO13VOAkOSgXzEy4zSQRfdMo3zhEzYNOHVPGj7r8PgukQq9QDX+Se2koRG2MdH/jw9cocrFseHIcu88kwo9nzDi1EQnlr7N7f6bZYN67wjeKyj1htGu1Kn/c17/u3x3feII2QLWlAXk6C4xXDPHa3InPY3fz7hJND3YdqgVO2GGTiZQY98DHTI6yZuKBWmYYgXhMqweA1LHRy2mwacbUGWu1m1/Lmha3O/AhOL1YJOv4xUXWG6ppRxsjJVfyPR3hEzgtOkW43bkyXNorI6yNepsYYiDOa3zxVeQ9zDiOIN1unX1fiLz2MZVzbpduE2nLQ+RB05J8wtj++lglFYzIP/7PrDusGwzPHrCCGTX7dqVJLr14vNV4DScV7xHmiQSwO9gr1sF7VKctQYYDGyLfWVc5PX/VES+/dR0MBl54KB5QHJCnmTbfKKzlUtacjv0rvw/osQfbK0kVcPWgSqslad6njVquGvebz0FTMBpdKMD1RpaE6bbhESdyZ8gwVpVPM8r4ns30IIcvbp52iFvjhvAg/T/T7uiNVMZrnlOFtawH+yaucAFxl5muTBGmGyu2HnfhXB+mNMoiAL4IftMZLltWsRLwieGZhkIebv4yTKJTX0hYqKW0VS208nW5ygpkJn/Pqg8iSWhznsyz92gSHIQKPoi4Maa5I39rw9FtZpgQPtV/2QYW3NstMVwjZVuTFLh+Ucm2ZgPRZan4yLXaWoY51CULf7MGUi9RuAAMTLgDtoYae0m66EI++HgZer/xss840hpHEw6UcPRSFNQYRu6BhXBJAhkmcsJRqVBii2Ck2maSOznDBSBwJipMRisYA4GbvoB4FkCmzlkhX/5g3YLV9eU84vLg/EY8r82F1SgvpVXTJVWhK51Jbd9jXq7HFWU17iocF6VrqTgPWQuEohmxUDC8HtvH9cUOJSkB3u05b9xn8uwv2o8p3scWZLpmqlisC90CYvK/1kW1oSXfAsWfW8f1IpFpYYte76ZEte9jZzH3ePorwtcF4li6LMDZN/9vQtoLTZpKPUGZV/BpcjrsS99O0eTqHS8bqRX/anvI1uZi/eGofduII5VvFiSzZs8DB1EpbD4Qz0t7/7ZXJAVaa/zRpZoMkIJVp9JXBVJtDpgtkdpHLcpuG2b0+SIl4WpvTRT483TMCWxsnzSmwAuBut0k06uZOb339vfUJ1XA9/1oLB4u3zVVQIwJIxA7gsaB9tg7gwm2w7AghLvGLlW3KaGgRNDYQbq+SbsLN9wR5wuPWNgMr2kDv4HxKwf3wBASyrynRd+371y94klgO5O0bglvYi2fbA0tD6QKtK2iUVlDcTYHHfvaTFVYLJGu2o+95yt6j5F84NmhxRArU5tMYgFkQ18GLN7MO94N6s6noCFVCrm4S1XDhhYkUz2hT6PQtea3dPH++TqHjivTxUl5oWTjVFv3ydLsvfXB6QPBBPnqkAiQRhMS/80bbwUz6ZWKxoGZqE/ozybFAYNYuKFCPOD5LABCueIXBjVewAvmbV7+9fl+ipsKsXQaVQNxrFJbIodktCEywEFByIyFtRuuglUY+AONvrktmxl3nMTCJUFLpB5KZdUQPNPg6ipA+KpXzXOeEJiuBl90yWuT3b/nxD+b45t39xh/Txs7V338oHKo0D6o1GE/ugS5vx7lzW+AVhdCjth3YToBWQ1OKASZu793SMDI5fI1srJnr/KSlxi9kxVC9ZnzgolpDq1w9ydZMtTDxXNILluaUUTgiTs0wkKatOBUIWjNiYvO7V1a86FrH1uUOvlKvNAm54c+qO0l+RZe1tU3G03Hszt36jywzDxrozSePRj+zhiNHZaovl1AH4YLBLpgh3XRtptzADu62XFrtNd+2/rynraiGgfHZK0qbHl0t3rfKb0K1c0yR1WDCIcWF5kWzeXzRasdv/dSEwvHnSwh5rIyDB76Lcq0TNeedcD4V+AVZQUHDlHtKE9zf/OuSqipsWuU1I0Hw7Cj5vD6BG19RzKYjo/uYNy29me+qegbEaVKsoeZJYY6CwPHEy4sD8OA6/U0lwbzT+ZQC5m5H187x1xDbpJxZ+MC9saNLAxSjmhc9d8As8BUxUzQIQQAKYPUHDyoBdK3AK2ij8BS6MY/dmyFv+4HalOIMehGTF6r61UP0kKVVyBWaLPevABv+44DxNuUJK5FJU5j6GlPFQrkg4j1AvDAJqEVA39J0sCnfzDsmC97JIqYIMgxBl0xBmKUWrjPHkz3hqT8y/ecJqLb2qCqFezH3Vhtuhp1ONfYZ5fVbAliYbl5fdYi4fHk0OB8n7FEUScn9q9MrwwNSlkswk9VKCKiAVoLUuAyuEGdhsh9yJBqgFFyRnEsHNfvkRfGopICzYJF3PZ1kGXUOhlCkhYkrhcN3FBwhitQjoXcNPAJKRjxrjaYajit1mMfmukaZCTzJGxqJmyjWCXz0B8avZjUkVCRmk5faaO7ERG/4VDX5Di5JlXy8V5DzManOsvJmSqx1PEznODs/fjCmfeup3UtI1WFbaqlScEjTTalG2F69Rjc9V7LNySAdk4l/ED1ihnRU5K2gTjJPTFybzSiVzIyLGgcSDQj8UL8EqwOL52H8gbb7Cvn/copdtutd8gFU2sq/Cj4BvClfPJNRz1LnaeyOEetBC4a+a3CsYrbiIvOk5L0VszEv7EClE6x79ZR1nj03SJywzkfvWA95CL3g/YccFRVcEvAy+tj8n+XhET21OOXSKj6mSFVyZ0KAc9pR+AV8zRL+KHz0LNAzCPpfVNoCEoofXKjoLzzElz8AFiRVgZS4UbbVDP5gHfxD7i4s5e6uyPTLfSGvuoG4w1krfIGB2dTJ9LlRnK5Kdy8Yit/YXE40RJvp9WQi9os6QVNx64nhq+XLS7AGJMZM4RGpgZc+l/W4rMn93WDDq3sUgCIasHAY/DhMrXAaIHT4oQBYm2R3l9euZubJhRkMZfbq5lF9fk+Mjh0qMTd+ZPKQFshp1AOJhNDaWdjA2dQVCZ8ioR8uW+BKY3EY7BhRLOKgtpzwXiLirAi9/Z33n3nL1d0/1ttrjOZzPxfJ5TomEsAjDX47EvxwMf89GcssIA24QkIzkpmHfOiCNZpwtkH50sfwpYHKvSkHQbW5YnQgMJyZsTlCTnFrJPrp1D1Uik/MrZP3nrm71FmUjFmVyJJRy0vDiAOvHsulc2Hk+iWGENXtlMTsI46e0Zx70R78ntp5Uq5q7GfipBUGrlnGL3sI08vMp7T/AhcH/mGgUDWqDBmsAvoCORHPyKCO7O+5RMG2ySwkiW6wsxtItQDMaXgQVdvtkNr1k7TO5HYBerx6QU6DPTYuGBAnVYAv8BtrpsGrD5InXj3SPzkmJ4LAtVtbwmiJhi7dXlhhSZtA6tGeljGFhqnqjP85O3wruVrB9qTKAkh/rx0JvoMJokAoer2Fl0B60zWEkFegNymwCPGyl7/sGmCeYQSYi///3/mDcUAZbp1YBcG7EWOz8gH+J4QnQgSN8h41dx+FCZAoJlobzKlPmN57BiFEDUhemDhGqDfpW8v5VqyUQiYBksaCozR+ibJL3F4mqo/87W4zIlO5zPzVxdZG9CXjlaJtzzMNlu1L/fsV67XN/eXUxMdU8JayBIynpe6y/Y2CPOuHa/EEoMb793UaryfR4hRpl1SHdPA3MgjE8zdZoU3qGdbm0WXe/k1vj3Sa0IBlhJh7aFObkJdWq559APJ1mdc3frAPxqP+uFc32zOny2yWFyXbIevhrfddsjZriTVA4gXMCR909Yd1Gbkihr5MBb8NW+Yxe8yqJMmmYq7lKI0dTlXqkkS1mk3oW8xjeQk4k6hheQZsKu0EqzG693AJrYVZZvQ30gLrjtsO67pQLna3k1ISUiiWgK00X50A/XFE++P2jB3Ivz5riGTGlmmAGREalTNd45tgJjVTH7dVKB2lc1hEnJJOS1/JlFS6r1BTbl6qp4OeObgF9sq8i5MRbv33iIkO2qpODoWxzorYrpGLnNA1uEdou3Uoz//U4MydrvmRTQxvrBDCWUH6tLa+ipGReUqiTCG+wSu6aRQ62j/t+caz6c8t/siXKZ2P3kpOxee0x359CWJ40ryLNFztDijtvzQCN/bz5ORBS9KMINmFoUd0JynDu6rhr6T9qnHEAa1eOWeSoFH12ID8yObO+/fz4d8TpbjRJT0jca7X+XJSr8Q4/LvSXWEbWBdCPv3+FbvZcZ88RVw1deOQMVXzWHPiezZdRyXMBufo7dFa6Zi/RPslfoOX1pVezXvY40sh9JJPBfQLlWJfOUtIqypOTHzFNLrdmHJ3b5Z4n7nTNoGy4aJUe6w60Iq1F+deoIfT/MS5tnraqUCiPdVZT4OS+D4llx5ukIzwNZi9p1y/u+Hav4DYIe+c9bzMmrHnWA2HR6PBjXkwo4pRwm7anv76XVjPhxIoKC/9aMj5YZ5nNMczjDYE5t3dg+tOlTz+CMMiGef1kmjVVMx7sJ83+TIwjfSMQ4WIHjCADk6Lm6hstgBZsVgKybnNpqW850JzdjS3+FhV0KlX1ONaKLmFoiB/RVv33nKBk+Jx+qQcO1riGPt7IC0xFs+TCpEkqMhvaWNBXao7bpcRpWYze5w5VXWdkTXqQzIw+xS+OxpnpAODTM77bl9Wn4M1VPvWRyOH76vaNFZv7ZGLwtIawY4IrJUZ6/bXaJj511L3Y61Od0FAp4qGFa0M5ee+W371v/0Cw3M0nfDjiLAKFtY4hFcx9Mp146TynjdvGM1gTN3t4qvnNwPLLy62DyX+srk39C4cXzzfmmXcmTNfz0xrCt7norX30ybWAs+x1Rrzg8prk9FqkuhvYiKt5/fwasB3FV1bu83N2FccXzfODe+v8uj6j8Ssb//MTVB02/DjheX9b4BvY8m3scHvLTo8JWzViCXxk1klLcMAFo9vqoRTs3IG2TLGpRq0qcrlJ5GAGZVGhUlsyn2LCSUk4VTfgLPzQDaX9aWFPtYN+E34ZZEHKvCEQF6AKwkpIUsmilvmBUZ2RAXqcV9niSECd8aKM6bIikbHXpxH0ysSYTpZ0MMys86G23SRzHBn3chqpui/LHnUKxP31vYr9ZM2w+7rvreBozZlky9rcsfNrrvdb89rjWrgjb4HGg2NFE088Mr7a2HfQjVh3a+zrydiwpnwKQ8Qqstj1UGXDLVM/flVohU6zGFoQActz7g7Ci/1dTmPqeHxZ2MydTNfEK/7PJkGV8oqnbnQbpAiPY6V/pavDxV1hJeYyxYpHXyNk05XDj06ZvUnHvHziZ0lj97NcrVKuUU41xK1uSDrWANX81CrXG/+nr67r/Mq32P9u7L/LwASK5MnDzw3FYgYh65yI6YFLtUwtxefrJ4MBxOzDBGK6wDkT3Inew9RZhM/d1f9RqliAz9jl4f4BQ1imUxf0C/79o5tjAjF7sQt9nrgZ6I/4Mdoo/2FQ+Hlh6onw7y2dzg/sz4/aCRqWhK+f9wPcgovrH0LjBzH2Y8rWH5M71M/2s2JgBjEzG4f8QWmqb43nk+J8FeLzCSr82I//vMK2+Q8X98P0sACf28vBlQoAs/4fW/4PKigYAAbNHHyGbvAfiu6HTeAHyQTzj033l7ttcbZbi+wPk8O/uGbhc/Nm/uHwflZPMNAkfIIBP/a+/+K1y/iRIv7FpfgDN/zn4OEHv3uuRgeIefYThxvDkfWy294uyY+tT95PIlQ/wt3nP9zcD68x3z/cj73bwj8Ptj8WLWo/TKU/4UA//zjQMwOfuZH/1gNiWvgnhXxtoVaQ4iT/i133B5fwL9WNf6aun/4QMzfZP+Fk/CP5L32DH18S/xAqP9AuHxBmnK6wX0i5u9Y/epaf3tRwnHl73Q70o/x4Q/5HqfGDE/wXnNcW60/Bqn90Nf86ovzP1qfqp3JaPyutf238D7VB+oOi/UHZdf84Hn93w/XgvrWr+pFLfqKNLfrJ9zmN58d2a/mnKOw/dlczPwImrz8mnOO/wGR+6P7+wL+ZvH/4Ppp/RNl/TkV+9LrpW13QslwTSz8W/0aM4CfKBpMX+AW3l39Vj/nn9l8jUl4QFtzYpH8sCH8KeVL845S08x9dR8WPCPxjpVXyI7h3dnaqZLuxKf8Ae/9NGA6qlF9w1r/Msv9FJ/PjIvlfjZH+RTdsCT4z828EnsR+OrR1+9OKGvGf5X/F/Tdk7Ai2KUWkOEM/FnapP1F4wsL8DM/5P7qvvz+FKvrRQf3Ek3okKrevH/iz2vw3sFcoP05V/xvEH1T/408gmdU/QqDOVrSNLBf0v+EJye79Qf6M7S7ov1BcfxK9ofyJ7sgc3Ovj3/wL+v6svlD+7RDYHyn73yTeeP5IVT8zhf9vylZqXCOHkOA6f1y+7MX+TI/VvxTt/9F1z/9I/zZc8U+KdHP/6OB+VjyXCD+R/dtmOHf/6LB+JJqfZunn/4Qu6Okmus91e2P4/EN18eNEP+JH6/r+U/iWf7OV82+j/wMC/8vMa536Zyyuf3RylT+xUP+rSdVPF/P+TTbQv63b5h5iwH17Y+zxr7b/nPzr439DhvpjRSf4g+P6wcH+K/tN2r/Auv+N679pQflvFP81megHUfeT4AmkO9jND9ufHw4AECzv081/7RH9Nzz/YmOT/LdFfpoQ+m+mWCdDfvbE9r9N+W+8fqBP5c72YyrE6BrHoNbGRc3RcGtjkGaTkGtjX/vioivtpJKSsQIEGZ0S9R9Mt3PlbvJLMssKlt2dfToGw+V8XLUKLZCOIOXFGaOMnkEUks8NQrcidi9vxKukCYORWLhJEJR1sqbdqtuwAekKsRu7Ux8p21d68zj6WEhcWYsoVyAokYzyV/YB8aXG8VruWUodCuqTS5NEq/oj2bjxdab8LvIjyd4cCd4SJ3rGskyD1dRlqNUuzqya7R58y/q25pZFbtqRuLFqrYIHE/ZJaxd3fAGWISKqEJZaxBtn8U7d40ccKT9nBJbrWus6kM+x4oMFub8MXSHdfouuVNXpE4iW87UXhzTZOKDqZjzN82UPuJT5k0kxoU/qYd5uDKhx4SZ4LdgQ5+GG7hTpIXKOVFASIVnhxbAYNsJfWKkXJFJtEfw66fmwt5gZI2ILmPxVOJTeDjQk3upBwp4M8bZzySiH5/Njv+qkcJXFOuviTI3JtLvzl4SGMi/NjdW56AVF7RHdld22wucu42v/YJDV5bKEoVn2D2oXYR0cuaR8Mvf5tG9soFIwapSEPT+6ZWfBfkvJqK3CUMK8f47aLSoXVNJuf+eVG8N7EkZdxpq++6nib/Mq7B1zvubba/u/T4hz2Y+pGRmR1WoMj05QlIx5eDj/lnSbC5ZCVtZe7ISpD67JmuEzI7kgfhijm+gNBOpD7tPqKwosClwMBIOYhj8D54TQRRQo1heBGEY4QqzC3+B3i77h2fUUUCnWzxZgS6nJtOPdJe4bDnzgCU6TDEXykVETVpN1i7ph353pCmZPlxNq8a9Jr4m7YdnFEtj+q48jSUZMRbIhsyLlFnODvXvjE+zOoM+jj7ELF4jZJwpS0K0PSypFrCX1Qr0rL6Dt+/Rb8gtdL/U1UD1QF96GgEv8L6mX9AkS44QhuCkiKoIN4UfaDN+KKDrTDB0UxDH8GMQzwpeAGUHgL4wjup9UhAMh+wgDrUEiZu7t+rni7Th2HQTib0j7NANZBEyS9aMJM/nJCCuIuSRfwPIC6Oxq9KNJM6XVJFpSbgh2BQXW4Psn8KVItMTUxN1Sbyj0WfG5FuhEEUwQaQg3xNz8b0h2Kf3TrFNFkSTAv4Vbkm6gd68DOwPVovWzhdgibiz7uAMrA+HAtQMv9IPZw24Y+yD7OPp0IXIQfmYn1T0QIzAokKLvVx9WIC0ERityTqBB32KgJvhioCvENuKv3/qppIg+Ei3Jdqz6UPpou6J9MwjB7HF2gLusgSHgjYGyENwimEdifU4/zdpGwCG1IvXiP8kyTTWEgOhTDtxGyia5wPuImPFN1M/mSxV9Qdml6YMKFOmDC8QXxTwC6XsNPIeAQ9TBZ0JqO8Y6Au9j6gMSIN6NCVyG8AQPiWKZoA9kD6SEYEViQdjCb0B6wzZOHUbyEVATaEm44dInzUugc4vUz5Zgi7HD3gXsGw+UBd8cwjxCCJwHT4G3weMSecHKS4Inp5soAK+H6CYigohB0iG8oKHLfJ0vMB5jTqY+eZteLTRvm64m207Irj2DOTBbn0/SjPMu+9PAV0QlaLR7YPeK+DE=
*/