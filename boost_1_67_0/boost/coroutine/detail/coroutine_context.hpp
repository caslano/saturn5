
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H
#define BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

// class hold stack-context and coroutines execution-context
class BOOST_COROUTINES_DECL coroutine_context
{
private:
    template< typename Coro >
    friend void trampoline( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_void( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_pull( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push_void( context::detail::transfer_t);

    preallocated            palloc_;
    context::detail::fcontext_t     ctx_;

public:
    typedef void( * ctx_fn)( context::detail::transfer_t);

    // default ctor represents the current execution-context
    coroutine_context();

    // ctor creates a new execution-context running coroutine-fn `fn`
    // `ctx_` will be allocated on top of the stack managed by parameter
    // `stack_ctx`
    coroutine_context( ctx_fn fn, preallocated const& palloc);

    coroutine_context( coroutine_context const&);

    coroutine_context& operator=( coroutine_context const&);

    void * jump( coroutine_context &, void * = 0);

    stack_context & stack_ctx()
    { return palloc_.sctx; }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

/* coroutine_context.hpp
PW8fOWGvDTzO7Bxqr68DFJLrguzIpYXKkQEbPQNKK46O0glvkt6ykateRWK/3hynBgKn3ocyqbZyGApQlwdiKlwEO6CbgZ9kY9Py7dZ8Ns2yzQlZ3xO0L6532kUjCZggLc+fEmgWVFdUIRYRTXfuUVR/3Pb62qGBZEmr+bWCM5Vgu4lwieYlLovDhlANbLgIQcNKLcAQVoubQU2yaFgny14TyYlc+wpB0bSNp3XA916QI5S1YXlAsvIFSzFPTV35aSTtLfWnv4kaw4fVs36MldGJfPEaZkY6XW9xpasKWbs4DtGZ1h1RFycivquzax82iDOb+LP7ckcpxuzfW+5OcYSO+EL4SeeMJq8TBMK8bZKrhS3503HHPzeIHUEfVynOVqvXej31jvikic73Ub680+CoIR647NjHfX7fdeTnwpKA54yXpoChktRdlz93L65/Vs5xTfLHqt1cEX0ihJSrdY1qAIXK0ZBeZjMGrHgPD/7uRXZut3Smt4ZVtO2zBiI5kGc6EzpruwPIDs83EtiI2XCjGhygZQEHIviUOJ24E79cPWGny1VXyE6kBXIVltQXA43bJLnZM+ZbanA3D8D5WeyuIhU5nFBjljsupxrK5DCgG9ATEotQtVvA1hnb6kttTN1mllYRouqfqbxNcstqg6xLWO/iU4qXskCSaJoJMOLnultLFRhtRJhCtC6FxYWtwOS/+YY5XRqndKU5D8kpFlxHfyjb6UGflM9XvkyGptmQ9UC7EYA4VxvjJX5dnZ9ZQTTT8+shhBkeIdCoGroZIVpc7bkmxYkO/zDiXhuayHhDd33jeeZ6vNKeBxEnWerrwYAL30qxlhcYrXpDli0UyBm4PFMQDdPtSz3HXu5oOz3cmwGdVvlEcaRpvVOfjCG8gnhcmcIkKC84Ngnn0bxOKiKZ9awYqbjnO93VxHiPZSebhdN4KUkyOeDnI/qGuf3rBrk1wLwW7FIsAgJkA946nI20cGrPMQVjWsZfRvUCIafcTgTl35x+/ZziL7QBf2YLDqLU3Rw1xeyoBOJROivpXJRGYOsOJXQYQa6b8Ldhcw9nt4F7jmL+G+3tlvrhFeoPNHfKmAlrni6pUuuEiq2h4465fpK2wx9mgLtpvstpjL6IpywMDCR2eVqRNTO/JLNQ3qfyd7Zx8nBWPKToEOHoC/ct67o3t6mv6nMY/ggcZzmymiKIr4VSw/cvWTuU3JsheYoZTBvUE1sV19g8OGc5PgZT+j1GxLyVEa+GeeIhG4HN8XkeDqDKaRvFmyyFhXE/f52sVUYxx7fRBZ1TtKF9QYcEJs3Qfx0sZYm8FWyLAIPbxEi0/Gf1mlVsqvdbFUuzVoZS9g8vDaYYWihd8g2bDH0OAm+38i7AWKp16Q8fg9eAfTzSuyV5UxjYLlCZ+upX5DLYCrZul0UYIEE7+R55ynKlzNJDKgKjAKEhgK15REcox8P9SgYhTA2yZPvN3/VlFfRhTEDfTgKFjmCYbpHA2p4C4M7KqnksHa+WNNzPNHeNRObLn0mZGUis5H6/0j3gw86Oo+I4LmvF403OL6t5rs5dSPzYTzu/dieOUNV4mDdnmqTWlex3ZzWTEMX2cOJFioVfHFeQ5d+9wMrGG4C1Qh8y/jlXFzDByyAc84NNILZ0BWanFp7veLWVE5my3fpdS28jIrKbt+lsa36diTCteioGPLba/r0k7QnoPpsdftVxGKGlzvb1kCQ64d6n3MjpN5FqTEdqS1Uev1iann1qphYlfps6oD6XYUzBEnSScOgcJh4xdmnWuIHneJapvVQeQFB5qnFnNVrSLVEfX7gvZHZvAxIifm7skWYDz2P/CikoWeK0o+kTymEOFztlXMivAAQic5crGwsnIaK5JT6aQlKs3rEjZ3IGO8vLt6ckP7usXEGkySQMWbnYScW/RHJreBAg3FvA+y5D9rciQb03trV98xhPbi/dUUUXa/7T5WaTZl/21zZqXa7zIxuM8Vv/dFrxY0TPro7Hw1/L1wHJRTyvP+RbL0P6106zGtHvUGoB4kcmHCbGo48GIswXvCFaES2qQ+xYQY9PHwF2gNKJCSgIIZvFHZ0IKMxfxLPXZfhycgW4R94aZJnHrca8E4W6HVRkgkwKs4+Oc7Vg4UvneXJp6hDSlorG+JYu6xOvNwK8z+A0OALrURvLmUSiy/nAK5clS+bAxzvOo25RD9sveF5WrbauPmyh6irz6Yd89uOkGa39wcT6SgD4KLACmuQUN3L2YNO2QO5pSkVfOFuVB3noaUsp/qJ9RkTjcB0dFB55TV/HWO8k1Mg/ZEDOI3cLVV5F1otp6sXswVkeN7lPjWpd7by/jlPppN4rpdkbEeFHIv9RcUwy5nkCzawIPY9LHKZXDdgGkWVCwG50Lq5GojNZkFB27ycoMzPLfSt2bhXJvoCSU8iVoVrStmOflXuNK1tFdVqa4i9xyZQvvhz5oT5xcTfGSPAowPSOO8rf6cWeDCzmCCOfSRsQhRjdXAgawWRYdJEIQkgdFNb2I/No7ftxIS5S4hS6ZS0WRrKaZU9MHqLfOiuABrQze5CPFK3UUSH7c71rZvYFK3WFSF6ltoTEJkQDtDD1i+nOYYlmkiIIj2yLgww14D2T6VsGum+dcDfpEqldXdM8JXFx+WTsd6gWLJvnfD+ENHXakLTeLEzsuPQwcekk58AhNHcrmIho9Q/1oMOX/ZwTXwkaEThEykOCtxsjIliMXQiq1WxHWt6vaNp4MBKsH+iLeUVcGUxR+MG61hc9mNoA5SIqPPXF8R4x3akbPuh/NT9jkNRkTHRM9oLY8SdRWFn680DLg2RNV3csiTEmZ83v31X+vATxEPFNTrXT30btt4BVJJB6n4DwTzbqKizUewvRGkpL1ai1HgUa8muvnXFoSpLKU4VX5jpKrVbiU9guX037nH1UsCSPtH3Hw51jRdCY0KRdGxh+FxibN0BOqxyPlmlzSM7V+izgQREQc+knBBL0TmBA+cmSefs1h7Lcyz/FwiZwz+AonxWtiVniY0j8V2OFK/Kc2GUmZ4/TprlkGBXfZjkHiAwujOPLMrcWU/+cpboGvC0bcZYiRwyvNTc+fM8HmIC8TOJZXktitLdAgHupqAiQgd5+IzcUVyFMG7znHR9Z5Yv1qrlGBxIiyXvQQnPH06neE1Lkw/4dzGNB4WjFXSHW2+8IJgVJ991SX+Bhe2L6thKdLdPU7NUj+CQRfAnTvMb0/7rfFcZEnx+HXmoIddrvsOKyzZ27T5W4aSuisMLeCG0hptB8HeHTQISK0k/jDp9GoYZawNjjGsdAtunwotBd+GYwwNVUEXkyDjoZViBJ+ntIrd0kqgqMJWRL2rmPH+1IsUNx8eE1xZ44BEar95ZGjUafsUSV/tszLngk69oA8kj9Nr7KOA55O0MbEr3E9OdI3n1Va6fGvE8KU+ZLym9sYibuJHcE4OMYhCPy57rnDIfvluCGByyUpg+u7Gx5f04sOgvz9MEBpzpZaQ54ifmYw3Bic/kUFuBhOMns4O801vLXxVAorTVzwd7GnfODVa+KJlGnzqIGgjesuIi2GY8EpTd0BVzHyLnk9q3PEfQ2rrnR/sN0/4krI+8zgycKS8kzoxLKs2Sw4nOHtcoz8pkDLTCiPin2qWZsNREdaVtfDw/i4tiQom8a+V89SDnaYfVEv3y1RR6/WjFpkOym/iYG4b04QvDYfqw97FWVZlju9diVeAmvrley/gwu+qqds2NnnBiXUWfzWG3xNnkUF5ZlXAMoAaXGuMuKzFzyA1OPLuudd9lbmNVr619MsL+BwBbVBkdByxrtG8AlMxBmFwT0mbZarq0kecev0eoWpDWmr+mMUpSTZYNhvANgU+C0Q+mi6Bys660C5waq/Qc2LXq7vwMtXJufB8kIlyq7Ff9EBFHZaBIZlXxqQM6nZh93Yj+nZdf37Kr5kTtC4KrjI+SqF4+4ORkAzVy+1rK953j3n6AC8nLfmAnL2687X85uDdYoRqchAf8NT+PancmnCOG1ONY4yQjiSSYEUpp6lymQWQWIhxzkWOVnfr+LaFf5pb9u1aTE4P6mASKD8xDT+L4YhjOpY2Cn9G7d22cbXZkDPePIs7bPhZ/0y70QJ9hQ8B+x7FQjVdDzTcTe0Kt8y3XPNMh+I2OZ5w54RXKl52D48j3SUYXy+R0otUqZuxDg9e2P0za7YtkC4k7IjxKeSfO1+HRuFBvFkArqgAwSdpuPRcjLiSehQuuowjlYsXnMdqUOzPocOwGwis/cR7FFPb6LiRjSnVH43InojGG9waye7zNiLRo1ZIA6RopBb7+ktK0YQHnwzeh6IzAo5KXdt+2cfKSRkbpbszbZN67s6FO+AMz/025z3gRiRJCDPbdvL8BlGd39UcbBZK5DRMVg5q+ydNXK9Lqx0v9rBvFTDY+5oNX5DnXKBOStnobSEXIgmqSIijV1CcylMkk/CJ/iSiwKcCxFc562xi0G+YdrnqYqHweCzMIagSKPbwaBe08KhwZjGMpeLqN3AwrzDpeN7+MXnjjgTYWHK1dmfGV0lx1fy5Uft2DtjlEFao34hJDwDNnvUD3sTQXEZYaOrD3MjJOInbbpbs3+FtmXMNwFQ1mcS+sWXOXkET169USjUm/shRTpy/1J6MyECJn8ekHduREh0jBJLZvLQnRbkksszl4jdVIyxKp3RZptmA2rcZzPbLyguimbMbsy1YdHuyPFm2QCsk4Xw4/V3eoZwFzyG5zWTL08KULAIbAJPqT+GvZabfxEiVpanxPax7UoifTZpvwhKHWA/gBTMfTlcqxOexHqN4rG33RIHnZ9I9dOJVvlZUdzk0TvdL+94Ly74FWIWZ1Mcp4VpN5svx8yGuTfoUOwe8yXdF96coU4yckmBb/8SuEQAI59d+WUUBG1quwULK0wynOSIj4JQIxNR23YlSSit8gcWZioK+7yViP8M9nJKa1R1UctBGyG144BK/TfmpXaC6P3+Hwnr4+NdglAWbK4a1QqwgBX838v+3NPH3HXK9MYKEZ3xuXoJvsqugWb3v7U7BblDZHKGz1XAnHucxv2doGAYIc2e48+ALW/KL+brxakdEGt2fouUOQLYzh/GI7hMRYGv8+8DKsOOY4slb+Twpaa/O50NLEJCZnUb7M1AZ5GqcNevFgwrVftLQB5wzyoYtZahu6TJ7EA8qVSq2yweH35a61wJ88oWIw45kx9S5pu0vqJ5gzp/m74V472infSzSD6ZU1cdhgS3gA/JhsqAINlZNTLeVlMqgeztJU9JbSgZL8Uy7SPvl3C9GFQJGpQWwDKawE6HvTdUR0P6NMPtr4yQl2Dp1WFkWvD4VnuQD1UTzhmj0K65jqVHn5zZ/iBsytmTzPD9kQV2U5pBEBm1U261XFtYCjb4jqFFiiccaWWYEFuQdzEIRlkWusli3JxdVgQ4UDvmzjUoqoJzIevd4rZcjBwaNGY1F+9mKUDsNpM8IdDH8rGzjx2KiL+y+7dFQ5cM6P9X72Ne82G6/cmvzSjxy99ESl3jpZCvIcNYViqJXwd8Dm4RjC9RdUOfZdKS3rHOqmNcs5P/HYHHs6jS9zPsiWnCeLXAvw020AY2g9YZvXVcsdkyBML0TPhLc/BxPfEFUSzhx6f0OxGBXjSA1y2+vCXkIKBNS9frKNMIMCc9fPCPmLyRvildUUE4G3+f8jwhHxoNr/3tpUsgmCUPF7900UZO37B67uOTBxUQzmogF4twn5Eb2HxvT3Db+wD4jHoz7UPvZ+srSziRRVx4cBWD/kDCOV8fBMDC5UN/0KFEMiMgtXwtG+Vdi/ZI1JFIsdzq2fTpSPEqiXw4CdyNAoocQRmjDgtWsu3eZrfKOL0qph7cs5flS3tkejXoNr8720qhztKlOhtMH7kxbpvxC388Jr6yDIUh/XTH9Q493qsd7IMd5RJSP8LRpUpBdQh+zWwynUsKxbgzCx1FZ9/ZRKLj4zihs93AzC+k6w+3VqxucL8GgbXtBBj4vID6ve1WcXWEbj1W+aFbeAeWHzETtLdV0rSCGdfxq8Lw9n3SfPCrhagC2mGfMDyAZW6F1yz79kOOuMclcFtfvlt2TfevPywEaAxRNdI/dxGY4c74dCXZCTdMBKb8d7+4yLgd3Q5Zy3yuCKJP++6wqXneaOO/eB1aa7zEeRtpr667rPGzq4PeHix0GDFFSqaAxl5L7s+D/L3vrLGSQnAwce3vWfQc0+qyHnIXu0txBnSdnZVQpVSmCGIpujrH2qut+O3sBit9oTih4dOnCMyL9wd63qC7O0i4CeuK0Zv8g0oEGpqs5wjiazzj5oACiz1058kcaA3azBl+lCESecQKW/IJpbqiC+kimzKouwM7EaxFlBnmorGH3fnq87+3ljVjD07krD7McxekYXm5Nz5Ss1wlDD8CpNuVSh7Gpc6rs8+usCK5dRCDJ1QssSCEAwHNZJUXrXRxj8mRUb3SyUKTYbebfcQ4y16GvMrcIsSPxcFpuEoC/WQh+Fj2FzQJWc9F1CJZ3Onvaw34Vj+X10TJviDo+PTR8ejsSI4+M0m3r6HslLYkFAZL6pNZoW7tWw5jaxJ11AehaBDZKFdnq730HQC1YG+rCAg8xtprdLPslyo7sGFkWDafool+tMiLtBW0AQp/15pEHA3q9iSf/F7tUcka31VybpgPakj7JVEHSBF4YXukf7FYHqEq3YqzOhAv8V/orYsf7IGn0J/chO2OICWmtIl1tb7y3W3NqYbVRK2VNpp87efNgUUes6cjJJNwfCy4VzT8rQQHvVPVAIZvNKspqQ+HG56X4vhVuN+VyPWRxYq0HJ+vJ5GqqSVtKU9157HinkpvB6mszHbA4lMCasPg/f1zQej1pkWJTCm0/ha/fVftBuhOy200TgxarHdUynPZm7Kw3CmREyNC1NvYufmhOKAgeX7JjMWRFioT42VLstdDEWS0Tn0uAemrKpIZM8RHXD0uWlCWmOAWScKfyt6fC47PzGw91DqzvxwFA6QwotSvkvjQK90oKAxye0jadfV2nzWeClPFe7rHYmSKLtBV713dyHoJ/3GT5VGVq2KXepYekUxEWnNvXR3W7bXUYkYGT7U0f+Vwo2JUpArWXqRc6XgAbprlcGMQ6CmM8IAgPf9CWQifevPb4KT2dDYhqZCUng9WF6Ymlai2btZ/uRBHUVnIMeUCxEhM/V8ax2Obi4Ap8+xk9uPcBe4KHm9RBoOS88tZ5ZT1RVikt4UGXS5FrSyg35G1ySlVDoUgSutAblJ2qyxQNOkYQohjAVnM/BpScf5CkMIwAyF+qG1DVFjXfZ+y2gPCBYiDG44nc3Vtd4bXT/OTGQwnUFPkwdpBNphWq8TEoPRh1yVREOdxE+Vv7Bpbpah68W1tTS7rhv5L0mH77c8FXjRrPQiZoKVbw8sx4PQEIvZfqxHqNVd+JMfnIsuMYvIcDLA7oSxoZbkhDBmk/i4YRwYDnHjUYGPsZH+cTGkcgDfmGKLJ7t/sozctktQD/JnLGCUhfXUskjVD9x3zVXvVIAKiheg3ShIfvG5nz1WUqvx3Swsr5u3sM1MoDOB7kzL2W/lLQUiNxT3D2jo4ktqMIkyPdyM0v1SlGAa43AgkRtqAwmLKDjijDCBlOLVVrm8a1q8cAF0FfVz0uakL/Hq+/rgTvXIt0cqjDv8H+3LC86+1RCTFUOy3QdzVIckJDo0sg4N5+VGXCMN5zrRLpBIHdY6CifbUOAsT8tdSaVbevV4yklrYt7R1YQzcsAQ339HIncsVADS8EG9envHvpOY0D2kEAMt+JiXo5tiZoa8ZoWqf7hRv/I+BqJA7MnenQ8RJJ69jzq9u1xzs/g2OXybvdBhSGKOlchEBRhN5ObUNejmLaFKA5gVtMv0f27HpKx/e/5lWdhlZVM2Kuc544CHBQZn1i4XKMUCkRTFoKBgKXo47SWEq6NFnTJiVNvmtXIgiNqUTcabDo0CMdYwLeJDdbOvbkuMDB9y+ndBRAzho8YfkzVNa02mnvIyYA0rn8iu5MNlW5cz7C/vjenBEI7HZC8KpoBZTg1/qfV7V4QDRdaLKsIWSkLp7BfftSC47ZtYba5+/ZTXmSRs0zGHm6LN1y8o6jEKLefYJ/ojuO6SYFE8HXlxi7vlDdMX8bdCHmsHePG+1fkg6DQdtK1Zr44mCfdWALca24r98yLkljH+seQ+84Km/8q87ggxFUHwEgQOoz5Q6mgXE1LHvK3D/byxe2LFNlmvHg8lVYjoS6thZzYjLXY+Q2O4m1YlcNbK84N/Dt251uDcHTVUvhZt3eGmOK13LmvNpRBa1ZWoHY7xcTdr6z15SPBObi/8L5xeDD2xT4si9A2HQOG0+ZVcLV+Rzt6LBRmRs0HZo52fr4PH4QWV2Pc7b0r1d+k6qN9/tm9FdoLC2s9fBWQYc5h49DQJbI/AP5pCH7XeG719WW22MRZzKwP5zzoINTYO3tgNNsBjV42Fv0Rk5R3FdzJOa+rWj87nJEnVpDYa9Sd0RCihJoPAdJOgz7S0SQeeagwErn2wO6Cy7jZLqQ5XxIrBjFIHfrdQiuiBDqCmb7V4kggrAdOCn15jamN7Fx/OtLuPUHvF71KZcTcMUBnmaQddOkQ1iBgY0GVg9Gv9EicT9O7HUHebWWXEZtdJ6CcU2sCky7lpOxD+zuoL3KrUgo5lQE3Q4gEL9WVJYuJHnN9UDj5NjodN8Si/rF8aMItUYSttQenAvNMsIFYBgROtuV6cgAoBQyO1QUJ1o37qplNK8Mi0cq7c73lNe4ihhJie8D2+G6G1HIpc4k7/IKyDaCQWkl20HSgV3EaAvUyMWTqUPZ961wEh+19XD2998uL5YKL+c+kLXmHs7MyvxHOnQ5Z2xjZFlG+QWeLnna/0KRkYHNSZVjnCN8Fd/2WApeb3w4VY8yrEBwltNqipDu2A5ZLIIK0UZ+zSM1KQxzE1qoJgM66evvWdZDisQMOyIZEirk9CSPUYctMW+kU+ELLDjOEiPgU43uePF3eX8a48VExAs7pAWrJIexwM00BJQxn2/MNlsQ24lxbCyEwX5+ajhqfxSJTkfLAwNLlnGe1/QQk4hrfYckbRoGAJJdlyyhLWSBS20sdMjT2geIDp8ock3g656f03bI1pFlEBiG7oUlBrxv1uoYjFEJn/Y2nSljGV5+9yQuVWQa8=
*/