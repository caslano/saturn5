// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP


#include <string>

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


    static inline std::string dir(int d)
    {
        return d == 0 ? "-" : (d == 1 ? "L" : d == -1 ? "R" : "#");
    }
    static inline std::string how_str(int h)
    {
        return h == 0 ? "-" : (h == 1 ? "A" : "D");
    }

    template <typename P, typename SR, typename O, typename C>
    std::ostream& operator<<(std::ostream &os, turn_info<P, SR, O, C> const& info)
    {
        os  << "\t"
            << " src " << info.seg_id.source_index
            << " seg " << info.seg_id.segment_index
            << " (// " << info.other_id.source_index
                << "." << info.other_id.segment_index << ")"
            << " how " << info.how
                << "[" << how_str(info.arrival)
                << " " << dir(info.direction)
                << (info.opposite ? " o" : "")
                << "]"
            << " sd "
                << dir(info.sides.template get<0,0>())
                << dir(info.sides.template get<0,1>())
                << dir(info.sides.template get<1,0>())
                << dir(info.sides.template get<1,1>())
            << " nxt seg " << info.travels_to_vertex_index
            << " , ip " << info.travels_to_ip_index
            << " , or " << info.next_ip_index
            << " frac " << info.fraction
            << info.visit_state;
        if (info.flagged)
        {
            os << " FLAGGED";
        }
        return os;
    }



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP

/* stream_info.hpp
bAYaQ+Yhd3O3ELWhmCDO9po6tt8EYkTDCpekDDCtEVvQklcmaatUyjqtEfpQRyy8dTh5pCd0OeDkgbAIp1u9YKe+Ch7WHIxLx7M3G9yawLxEg9NvxXvEaLyniGJN0VBFT+yXD7hhDXv36FzwKIJQyvCOtKmMVw0vmUhq/hm0U22mVXOmhXOxWjdSse2m1UYD0TBHb3Amrbem1fIig1rQKR4V8VraWxu/WCsIfUK1VAaSzPTKzMaFqhe5aP98+lxoPNm82NOpKJnxo3V+OKlZWcLKYjxWry+RIUmnmo/riELPyWxcpLqVwwxBazM9YQrvszDd/0uvNql3ayyLq9WZjm3LoMnFtgRsaZDTIDoFM8OMfTmCZ5g0aiigiJUPHEAc6MtAvlew1/ldfWROPIk78C8yU9F7+JwW34RHverKkvffRPPTousiXC7u7dDG+p8ZpbL2s/Z087gnpIRXhWHU8R+6051nrmmQad5J+TRRZy7dC1Fel9+aTjix5OPG3lK/WxBdmWsmD+jI2ZOsNgdhQvcd0tIgdjWFtp3w6DrWdX74lMt6QioMc0fDv48Lthy37cknGV99W31X3Ehz8h7JAAAs/9PCEJRgxy/e2Un09QJEhrjL5rv8x/xONFy+kpVJ3AlFdXAz298n4zwg0tlfJWN6r1Z2l5WXR4A1GoBh+iL+wZLNNpeesyExejFK9E/xZDVNkUDRuhOQg2j1/dCDH60fkXfXocfOIVqK9BlKxyBCs/0ySGM4W+FNtHYYcp7D3bMi7MJ2mrHn87QYnaL/oCFjiPZglgBuSoz2nAF2xD7nLPv57n4XFrkPvz7A8fmjZHJ7Td8Ry35K1R01tPL8rbj5Xp+L4M067+WJ/M4H/uJ1A8Mtl5qh9YT0lmWkOnjrZNQxrjDgqLZz44NPA86DYmd0PxhwKbLt5v18K7Lw+BImsTUS/oDZEzVU0mHqJgifvuBDHmycUjhf9k66hO68+ofafhSElvKuv90unenDJfCW9q/NpNHIl7fOpjHddiXaCn+NwNAoCcUr29FucvYiumXC4VCfYSnOh4R7ddTfdzJMkXvxP271WmLi9rL8is4iUx/g2GnSikfx6AW/2gzJt4aLzp3//OTSvS78bGg2zhxqPMrzf5ZT5S4p89w/P6N54Sy7Tl+Qfr1rru8kp+oRZT8e2GfMvh+W8xoQf+gc6+Fir+Ze1E3tWDZuXPjxROZQczWL7pwqe4Xb4G7tkO8/WaTlvOJevnPBGL9yxSgMPC0hPbmi5Xi/NezQeEC4koq7Gnybyxwy/c+OUIetAm7lnVNg+e1N0Dp+AyxQ4kKhkF8Qy1oZe50fc+++gj49N0o6N5JoWnNaoO9yOqz40RzyVyTsW87rp/7J3jXkelOzcHFkXbkrtmrrsItXVa+j0GJre/1ls5PtTVBuEZMrsit36lxPwuPZ6PyIe33dLv68wl3ZUOVft8i1OYdlx5TYpKj25Nl/H/4KRnV80oUD9n5C1jUV1npPuQLR4bTyUeH8UVvSoW5+isU/I0S0+EqN2g43Lns95JK2V+xUvA0jzwTP1yacf5N7T1/zj/T8e9one2mXRNmRR+gGJziUwewcJTgMXOoKSreW9As0NtpnSxow83DoGlh0Hf93sUf6kQU3ffaWlSx9YeJDo0OxYTJnTF40fdY2zMzyRBd5hUNt/Mz/x++7lAAE3beQxnCmxOfJT/8OzX33Pf4wcz7YQWlGX+XSG6I5rnGct/VE6LeZZfLo5BK5dNKA4Dey6jV03uZYY+kSx8yn2XhBsd0AjKzz7qgwHhJIJPT3sbHQ6C1XtJF0ak3zaNt762RGA3pv+1EtbW1KoEXrC83ksGhbWeWzH7ZNvj1kLtJD2oSfz/r45pq9rq8eIUtq7B7XEL0yiIs25MR9C4Ln5L2Vwqfi0RCsI2LK4bP/4GUSvXCiYJb1C6Hr5DHrwCLlgLdsywzdmFwvb+SFdXbDzziwdfqedFCk40eUWxXMDmtltu/ytGIZ2QIoxyRW7gpW4OaKpKaF65tBVOCa2ORP/Pt/uImikKfjaZv4s+xjxQFfDg/r4wuXEjNw1ZaaXcxpFi+l+OFj9Ox92M9NnW2EnOssXunxzOk7/E3j7Q8XgZMmGa8L7e1m+zuDKIKTTfb6ExcOx/wHMLD32WmMl+vuafo26llA1ENL6m93slT9Se6oLkmDh/tnIODRdu1I153kllbf+9cq5468gwF1cULNgviqYaSRoYvCWgHfS0m9YNFgeJRfMcNEUWH3MfeaggN0Lvj+fEw7/fF9CAnIEaK5p+2/rciG5wZQJbyywT5kBZ63YSMgJb47/XEuCQowqPb8Y5DvGeKni3haFy39cgIH1USkfB8ZP0kQ0VtjAaU+c+75B9A8RA06EPsBlMjTwfzAlgWEzIseYLnJo0Bx4eJQPl3Q/LjkVfqxCggK2KYp3d6EDQFofx0j8Sj3CuVf3sOKGGXGj4/rxMaKEK65DGg/+pKgS4fpOBEJ+3OTnGphC1KXdICq8t8HoLQDrqC2Y+Mb1h58LMPdOPsR8mS3E0oCiWwBpX1akLnIl0PDdbQx4v/9KD0rG01dY6l5pGNIgYnzYn7JqXD/jaXKwshM6lkl9ZqBFiG9xsYq4q9zQDAlKSYW3OGXcIzbG6o71nOsvplC0kOJH5hMnIuJrwYpMeQrnfqc1r9X/s7/Pa/LTlwe7HrKETfhcw+/ze3hXll3qQF28YwIk1cfu+NU47T5EW/WF52Vg14SID0TaaQQQU789nWKX2mvuiAFHURfSKizP/1dthyV+wxL6NvtQhENmIDTrZ9TBayPIq0Ffj+hKTuBQI+CKI4HhH+bHonq9qNR6kG+ZEEWdodZBjgGOW/l1eFOT+qw7Z6wMxugCn142PworSD48U8OWM2ASClNtiKLRReKuhCbH9WSwT5amIe325TxI8uSb14PEpltYpg2kcGUy1+DflbqGxOaiZmCWn4ZvtPNwXOuG861cMDHUzCb3LdC2YLFbQXwL2Ir8Dp+N3IR5ZFioyqjX6DN0jNy/Mj9531THhVxAV8j23M41XeR1nfxnrbNKmvodHu6bw1i3jt/7wnZhNB6QlJLgRDMBWrCOw5+wrtbz2+HB+m/R8MNP/um36PSyt8OqQUI7+KFPN00xr1uyg+LbG+8L3bdTnYfeWh3+uJmNpKd9fsbD07lDGtbCcCBbzwHEj9904iuDCUCRJlh795kEQ/dVP780RccWA2IUqDqH5GLmsLaP/hX9LaO8lMwdS4GDW/9p5QgNS7Inwf3DmxcerpzaSBw96J2vG2xUvbO9CEnCXpkCX1x0aarASDPldidLhjsJ85w+uWK0HjFWjS2ENf12NA8QurnhF2aHZbLRgAToy8ORDGQ73egsPgoSJDUyUC2u5sPNhaNLyIiNAV2cGPuuyxL4ofUpqBRiMWeHbXQM330zaYHyV4bZB5x5gPvU8Ab3ucCJIef+Rj85nmdDLHvMreTvX1NEY7QuoA5yiV527caBVXZW4rnlhBJLcMfm5dOfN3+cQxB44PU9HGH9v2iEolahMB/vNdj2NkOFufWvX5FHX+/+MYADPzG4JB6VHCdjl05k9auN6gIW5jdQuqL2lthxJ8OMbatmuhb6T/6CighynTfz7T50/3kUpA9bQlERDAcDk98NRw+rtkz/cidC8O2QyhklTAs798jXw4ZELZFCrc4znbkQNgeqWWjupBtJSRB3aIAzsavoJAF98SCY9tFmkMSbpUYYgDiNRAitZjgh7ioq3aklYjNbuWrN3NJ2EMXjZ/t3x1ksJR39DqezWhWqHJ1k3l4dSpxeBndzKNeqi4HSvUZ/QWTnFwqX+y01pf5Hte9ujnurfVLQR1EEHMSUKYqBRNE79Yhpq+H0W2f9ReBQXRVX4++LiSb8++bA3L9DMmrj8RIzAZB6UjxrdE/MMrAG7u8iQIMcMQHC3OBQuqHPIQa2viNq5OdgDqP7IUN2lhvzEE6zT9ru0NcSJd8Qpq32Nb3P+Fh7Vq9wxkH/sOZVtCbic5ZR6NwgQGKM2Y1WhsZ8aZxQguz/HZMZQCnSDP0+MsDsgqBErLF8Hea7N6buavnOv9Kg+cyRAKvpjAJg6u9u87pv7giD99EKr+uO2G9rbP+vBiw3KHSoS7sIkSy2/aIL5hiMLW9jv56TxH1FMrQmssu2fehhwk3I6+MK8Q1p1JAdmrxayOuCUUbIX4prBIn5KhDPPcRpt7fop9bJ/EPF7PJexLSyt9Zd/y6Kx2Ov11E4/6pG6oaTifkjPvTtNj79qr/hK7v5E0/qBPS6SnXK//bNjzqcVDApHc1TJvXegTTNxa6ikwTMR4fnM8B7dF6gBH43a3SZ++ciZZ+RHY0c1Lf1vctW3N1C6liBQtlIOznb0B6Oxt7gH49hPHvJeBv/4eSyp3z698X0aV/wGCLqFm2b9Es4KSP3nE/W6YYlVddS2ywjvyuQ7LMtcO32/zMWyp6+PEOBqlF/uq5Nx4yywVJW1/CzJq5YwRjE2Nbumrc19K/5EfbEQaP3Uv3c6YfvMQrgEJpHv+KGDWXLpPRNwfUasjwaNsajcNxWvyRwhqwsrPB0ddtvdYvDxLZY0U2K+tbX6i0RSySTSfSVmP6tIRZxV6YjcsMFMRIPlKrYix3g52QVXGQrBwEQ2TbdsCokOIBa3+MPcH4nZq+WLMXgswl0IkJHMCa5eZkaPwVD1VUsr/mqy/z3QX3SzZqT7vMlIc27YvfqIch7ckzhy8F0s6PF3BFAEWHtanPvK710sHwsgbNdvzF4q5Ih+wOEHCl8n6FRQ9yjxh4jOXjFw3ZG/nvJSLE4Ue3RnDuxM0nsxWyEwESQfMvRDe0KsF2r3gVqRh727HWg+iynuSagHosUjMMxV7wDze4X3hHzu49rtXvERB7EF7tb53BhU5vRwe0ewiDKOD721ZwSR8geo9Aq+K1KsQw1LcEHkCmJgLWSHgxlNgHoA1DiPkB9AMQx3AaMNJOgG8FPIRmwJBlzwPn8xx6//6ywwVySf7UldsHsA5DdPgh3UtvvsEh/982FxF4ZIP2VulFeNRDLu6emsg/LoQi7se+KNSBYbDh5E1Prcx+7k1FHHBxl8LoxYXGN/YnNiSCEBLhDIYLc1iniwD081LulPdRkNTMQIwqPtfQg/PqRwwiQhXV6H+W+XqbG3KbS3PCbv5iQgtC7m+h3Knum/n9Usya8EIPIj/sqEq8x/gGCkCWAdVQ3/agfxqFYA0A11g+560R71YLhqAQiB4lvCjR3eZG3eaynIi2SuXm0u3RY3dDvWqigbO4B3bcfK8yHsLmX+tQ5/Nd9oXH9rvKFeVLDKmz3eRFjpNl3yDm8xBeE8hO5ZwiJyhdMgEsuqcbb1jTJzp2o4X7Ocz4DxLr+4wb7Z6wB2mXmYfQ+0JwLyE2N0DdiplnV417QaSdGNACMSgddeeCoOGvKKPGzZZqoKiwRmG26Uukv+Y9awhFIEgczZ9jQJQ37/gZsxvn9YMYRI0K8K/JgPgSR0C+R0G+R7s7V6XJ1RZz+EhjP/i9+iSvp6oNptI9HHWGsXPFQWyhJ+kXHnvzXZmS6iwKtJumj+2w3MZhUaYhv74vA3FGQbFmhy664y/P0SVLF5lV+JxgSYqslPgpu63DquP2ksRXoGsWRDHVRXSpTXoc5L2J+ij8V4HgmeHLKz5at8/XBXvhsuNcOpDm4bPljR+hf1uIqLDEjTDnjW0oKv9O7w1Erp+dBvTzUMvqpgq1x6c9Y0fpZWvUYyzp/oIIrIMEMCjefTeF3snrAyqSblc/0/Q3eHKobHUz2xzyGnvz7mW8Lb1RLKgt5zJ961ogPvOi47h3iJU7h7CoQiyMPnJpT945QBHY3aE31HGGpX28tGczOJvgtH9get/PZ5T7pSgKwrHweRJ7q0JqRt4AXVk7fTcU7dJT/z9Au1B7bpWsu+V4ziCUO8K60xQtirkUOxXb9A6UvhDbS4jlTRcRWCu34jU7xEEabIXmTzkA+AjKELWCiYCgEUJIDkEsYUCQ/FQLpj/sHQr3C3oYJC1kR+JF8fDZ5mamegHQ7e9vni0ArqIBVxFCNKPd+bw8/U4yKqtPklyFcmWVo00uNedOao0FqojP5OVSTiS0RTWfUlhyE/LGw3VjRqVF74SdG99xxgEoCfnd6PLk3YrCjTUHHxO14aHH1DzShyYG6M0Q4rNKJTog4OT0OduaY2ZqzHirjtfC9WLUwCC+3H9uUW+O/W506BnicuTfkRa6U9c2mSNzf5OWZp8Sa/f8Yak59FO6mkGO5M1VdqAkwGaeI+2ozuP1r0A2o9dXshUhIQi9UqGSs4JAKPHr60O9QLZvQgzSQt3R2cjvCm1yH0AFT8XTf3rjOBz++K+8hxf3ohKQnoR/hZ2ikJo1c40o9lGC15vpkQ9D4jMQh5mn11ZqARt7EftHXO4hONHVNm2aMdrVvOh0JZvb4Lx5zqWQgX0luhXiVZhFMXRjIfti3s/7VfQzXfTfzAiVH+fSg9g+6/RSQM+G2uKztrZLD8wzh2q3Q+CuEuMX8CZ0dLcM8hpErbfzIl12WtSosXhx7xYnlwlQbZiTb69mv0qzfyL0JmqfuAkguR1zSOxW0v9JMmHZQ6tDUpidJDUNMWpkLxHjJ1wYfRWNmnJvrMPJLAt947GYPcYxxhld3bSieu8hqoqF20Gq3xUUw/elH4V+B0bhr0La56HfDdVYbsh/khfnX75e/Z63pAbLM82v+IeB9Rr/gKbNbK+VCHxRCrMlG9GlbOjW7aU25Burh97Wa+apYndKJNIhCWxPxQoWtrnTlCc739ZPUf+j5wjOAqj4+vnA6HKGraiN86eNu5ArJ5SXl3hHSgq7lRPuQBiX0xbEcrtpRBSY557PruXjLWAKs7ORQFqcdcA0pFvS9E9KZXxKPOaqrKLZuk6YuyK5T+jM5cpXf3jUk8vvLE4an7jgvKWqTfJCrx8F0f9veQpRyz8bhaOaWVB2sMawnz300runSkIgQoWPekr7uXNsBhjdIZX0tzOrh9hgRqmN/xphop5I5xQZV1a8TVGuhKTed9biRlbq97zI2qXMJDpH9oH5Noo8iztwLx2Uup3hNubzAmKgc5NGUZyrkKk3HQjaIZhrHbeAm2P9CU2ZB2jf6yHI88e7Oaiuawy5uUV77NPB0ezrL1gkLcjHa/UJH7FRzUmW1IRXTgWsZo0wpy1yMTcdiXXpGTA8CxFTeMN0lOGXgO2CmibMK2gpG2nD8wh2/OFiEjuRkQtezw8O6c7Y1cFvnc5j9zOWJzhXSVVv618LskcsYw/7XUD21aMd6XVtSZHAbaxM7+FhrtgswIDlx91NVIiQM3iKxy/Ts//ZpJHnEDg90OB8N/oaHnUFlxATPBczRX8FaY5vgYxvn5PXfHd7d6C+6kHbAGR2fmCMh3eGnUgYaB1LAOioKM6fG31Pcx16dzLvht6tAnmOs78m9GhK+cRb+hBdbZGMgYFXb+ttPy8mLA94xbXTPunQPqR+tRPrrtun8HRD8ltlbJybfeGfObrh4aqARsBGTQ2FcNcP4W2tbQ2FblGxpdgcTca3ORwmKjZf5iMnLFnfiBrTHIIHIw+opMzCH0LsGlFX2gnTXlI+73T5bhv5NX4Jll1EVfGWaFHNWZb3RFe6PzfGLdkdgjxf3XDSIWa2dARB0QQGJ7jind2aDOuEsUzHndHi8xCLRrI0RS0qfkho3Su+nT9TyGprEaIvqSHszCKMpHKPkArsAeTkbx7kxRkrK7i2FHFaDJE9yAVzGbePHzFdcjf4rtoB4UBCAusMosFlRzCXQXgVPCSu22d5gmlHUDhFue4vtaEedRKPF+mz35bIHxt1c8KxLpoU90ER5Y4+t05U1QYLmmai+jAcHhZ7se9I46CY8+Zavy3anRhUdQYzmtxLMZ5BONeFCq5MG4HYV7RS7++cN+9PnHstI/bFBj8zLf5M6Q3TEdppYpKgmKipSw1DoprRXoFJYmS3YkSLWBAWnMdfGAOthaQzdQwIwzBHvZ4FWVmQOuncusasKADhFZ28g0sbQ6Lq8LFdI3+giH+ASA5zePtNpPNcjyNn5Vhm3fVO1AmjPb7ddUjXW7PcLI9rw40fuUliOA/tIF1kndWO/Lqo1EYsCKofaGZLXvUlkwiPBvzMYecHxw+JmEuh7qmHfufGK4jCIdpwocmmk3oPZ42bFtalzIasQjvd5ur+B+KKWomvc41kiGR0N+/6Yjf+R+GLyf0t/vxnCuO1p33OnRORb+yK4vnN/GK3KjsMeE9/bpozZ667NbGNKZiSMU4cXUXNi57gMTr4bUu+I3UsSmTHMBcj2DuZbD/g4hDBLhI1xdHPy7GeGwe0D65AMKDfcytXWLTAQ7XJid4ESGX+13jN/bbO9DBkH2xRsQ0/s4zWGrMq648RnVufdKuuag2aFenaoZ5RT3zdeB3p5n7RLyWO9rjl2ALamYJGXrwh7hwpidlyT/ES9ZAtsSdAvtJ1zMWGdIWvqLi2hOVzsi9kRGwa4rr7TkGsd+AuVOEkyA+Z6pvkLphC7yRfZTtfboiyo1jX20Z/fhiWNbowqHB4/492VURb5k00SkG5COwXca9Zs6W1mPAMsL79yNWJFqZPfvOB6af1gYH/v5UwAvdT39eeJuzxisSklXuE9Ppqmg+A1EU3zLwXbI3SNebZKtGGpCVOZ3AjJEoBfT3pOsD3ivLMa/FsI+fnxoyMNwphpmD56BtBoV+MZSahHezc07f18/K9d9onrbFnyAKhaveJ56ujsdBWrIuuzf7SW/S15FPVyMfiv+lMXfbzTqfHG/2S3rd4v9yKfJkuqTUdpSeISfs0lrPDesFxO2/cBwStFdIjNt3VQTxzUkX3kQt/bPu1MV0X7agbs4bKM3rYxriJj1k012hZK/F951u7267+2blLpxCJpHaUzeCHUvRdPWGvb/SaTDdgbjQLpjVxEvBt3bLgyppUn9yn6pxrSA89/r6GI/Y6/NDLN/NlF/DfTjjwD0/O3HYHyvh1oP6/DxNbcLfczQznOuyhBWa3XGL3FFSjFQ3PdpQC+7pvB4rxS4l+gUj0b1uLS/iNE/fIB3cuHptZutBVVy4e7g4ZSEv62kYISAlxJ7yOqAGhB6YBYfw3iFwFnm74qcZnFERQiDbkWvAtmyZhWnvYnWKd55o=
*/