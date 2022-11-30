/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    mutable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_MUTABLE_H
#define BOOST_HOF_GUARD_FUNCTION_MUTABLE_H

/// mutable
/// =======
/// 
/// Description
/// -----------
/// 
/// The `mutable` function adaptor allows using a non-const function object
/// inside of a const-function object. In Fit, all the function adaptors use
/// `const` call overloads, so if there is a function that has a non-const
/// call operator, it couldn't be used directly. So, `mutable_` allows the
/// function to be used inside of the call operator.
/// 
/// NOTE: This function should be used with caution since many functions are
/// copied, so relying on some internal shared state can be error-prone.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     mutable_adaptor<F> mutable_(F f)
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [MutableFunctionObject](MutableFunctionObject)
/// * MoveConstructible
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct mutable_adaptor
{
    mutable F f;

    BOOST_HOF_DELEGATE_CONSTRUCTOR(mutable_adaptor, F, f);

    BOOST_HOF_RETURNS_CLASS(mutable_adaptor);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS(BOOST_HOF_CONST_THIS->f(BOOST_HOF_FORWARD(Ts)(xs)...));
};

BOOST_HOF_DECLARE_STATIC_VAR(mutable_, detail::make<mutable_adaptor>);

}} // namespace boost::hof


#endif

/* mutable.hpp
K2NfvtOg4U6jMLpT/26Wq2bvv6w0yUs/kfLRh7aOh1ImD9Z6TEAQr2iTHA5E1sXKZQt5dx3tsBzOnY7koIgj44G0S+royJr0kVh3p2YwyzendiLiWIxLpwD8wWYlHJFyUM1JTTjeLmEXqekOK41ICPCYO5Xu1rpDp/ZY2niFR65+ZGgkSjq7np05/rqqGyDwvfH3Jc4NCt46IjF5pPPlX9mXxlV3cmo8cj0xOPHrn0ikuG1J5MZiNwDGfWeZur4FmgGM91Mnd4nEAoG/Oo79lJ2wLUSBfqIQUhRhVAor9/S3i0Ne4a3OpL7R0yWc3b9CsowKpR3jUbkIbPLYcoa+SXfJKoZpNXVvLHulKndFPl3MvTHTaiX5bHntRsk/R9FgFtiw/ZyLvdf3ye7xiQ6ek9l2oHRZNc3N6e8dQsiW+mKN9WtuYZnhFj5NjqECoWDwgTqnqGwKedze1InN3Flqnh9Ny0rRBmvkw/vMMeaWfLPlL7auWDFyrRM3ifMCLFMWf451UYAJRKnWhx8dPj1NEiWssFSDJ8TVxkZIklv+vxt85p9fUV1/Ttms5+k/wYcHVOEfxC30vE61LHqNHEd9I1/RobajOCoJRUt4cnCvHGTa/kOcYoOiJ6DM+RP3LXmPq8Le0zGsE2bRU/PLtfRYbchBUs3Pn0p2P/IlVjWgupxKTTKjxgswi/62PCI6ZDsVLNF3rJK1CieusaBOwd8/ax+XBDXDpUpFtwoiiAfDdes8xMK5UR0GrqP/HvmCXs1zy7a7rfBCycwrHxA2sqB9JzPY4/psCn0Z3fPKVBRTowjt6xRw5c1plt1ZkibQPo8UySzwl9vtviqUdJtmV3zluMcm/hopDr0CYQvy/F7ENCiBvwfZKBKO7NRL2pSCKjX63Vtin62ixpBpYau0c7fnZ8JHGKUyL+vg/jVyWVBGNayvCbUada8ZKhclm4Sb0e9HwjLlm29tqjAg0RbM9EIWFw6E9ueKQXGL+l4UEo9Du1HzYDvMKeE4rCecX0qCgc6cfAJhV8u/KIPoIVG9Z7pkqsSzVI5ZvnBvLmf1m57a+TNFKDs/jLbYCNtruoZ/49HDrNgKKoxB5WisrBN9DjEiGkuzPO8U98AJRn4KKxEQ8YgGoij0brHPXLCbQzzpqLCTI0EZKQD76xBBWn15ZKCKnRrYAN5WENrdbNhdC04M1GlsCJl0whgQEVwfYobRnv60Eao/Riky1jc1ZzkQw/7eHRJbHCKTEsu5inmsa1XMFnLUmTCokXsnSTjnU005mz7yo1mmKOtovwLa8cF3AplHde56PnxtN5Qrasmzj09xrLRrZEBC0zGzDWPM9uGQD9HmhHIm5Op67ldc0bVrgi5OWp8JaKkwbuSfWxXCP3dl8YhUzwvTGx6rW4wRiB1ORyUaM6qtmqWi0EVgmAWRtWCo6vR36t2f9tHfMbsUYg8kLugaNWyJM6YT39v0XmepmQYkdT+Qmbqs0pdnC6YW1LAaoTvD4CwO3SQwxol7hGGl6EKlbSwfcMole+F9q3bCvJH8ZosjlnnLHIDl4OltBaJKI0X6/L3BedUt/WDtG7gEId978Uupo9inchlpl+rzor1bow2kQlRDuk4HHh/RTjDZfa0YwJ6nfkP1CrGiIWYpYe+sOPbvHdb6l2UuvbLJ9SAxtpW1+bwPVX4pQ/pqTty+V59DqPVn77FgIkGoeHalJxFx0qu0RnM4FQuODCS2bfTRYgP4AEJ1dP4bCbmUHMHYX3/s66hgfk8dDcLnGaPeb3/LTjTXgi6R0LhspkXaX5UXK1Fl/nW4HQLSLdD6jU09vmGAqWlMTMnbgHQwvnGq3HLqduj0cO9s5naIm8gB9t7t4TKMRNgoFo9ZNwj7xtc5KTSNS3lZJaB02PNXOiYgX4Ym3/rLJgDbl9AxRqi5K6ksQrUqPexQknM05a/ywpe6gHcC4rtvjUU4f//YsVE3t5c58FVuTBwHTacVWc3VbHPujtNNJkiexmjcQieTp7X81Z5zPre9ps82VfKgUKyvOBsJyoducfT5U7H0Zp3sRyypR/H4N3A5RsL5x3kAyI1PMh2qqWK5ZValuovF7opqNyqyPDvTmzRzWHffVx2xKxgrrCfGmRFnivx1VJtQrjG0eV9d/JHSSCpmXdFFgO1Rk64210+TP3JM/qGFZ39u5XtYXOTxAdH2wQ5irHWj97bXK24OWr0FssX5Q6iebHy7ga6T1u2AzyhlfGFugXIkrEZ82/ZYEjbOZ+/LCVQPkIwOTO8Evkpr4Jro4K6bysJpaVeCPmQjXUQLGInNz1V3nWlW+64k/MBsihQz0Mzov5YZYv+Y2ZOmIoxY4AtesKlxs8Ma/JnZqQl6TAnPwRnFDporZfxBO6aWbOnJRDp3UAvylAYTvPBjZhsheiB97c58xUi6/+CuUP+lGT/MmuEhHaVed6hc9o05+PjQNQ5fkJ7gjTpmO/dajFAFZewYL+sxfhiO358XoEKSBTPCJmYfIYyViayHCdgbVeWi7zhlZxzM6zuOtlqQ/e7KoVO/lZOsBaX7foknHBlbk10yUH1YX+MqEJTG9QVA0imXRXcd2SJDdZPTFkuYpGcDho8DrFBFrC/JfhAM0//7LdN9iFYiFAEUHPwscZbARp0YNIZsWXxuC/1F48rnqCQWrnHIJG2JsPjuTislSLrdDPBI7WYFVoeWyk1WbchQaUWy5KaTpk9ko7+UBRbp/SqiddmHNV0sIwUVwRZTC68oW3GjSOrS6LHsOpr93bW+1QFLIK0iU4oR/MWkQjioXPR0gRdWuRRvaejEVvmO9bB1R4XAqnVxzWIy12TGhxeIKT3W3f4r3iy4aY7sEs2+RugdQj8d80VsX/7DMYFFqpq0OyulVEIhAbrrgF9ECeOeLGSv3afKzYzHMSXJkwqyfzqE6bZk+CCBwdRo5+S4ZDG8p+J6tVCvY3NIuDYkNtzV3aZk77XzR6IQ0rcLdbNnR91ycaJNnIS/XM792FBjPyBAZkXvSu+0Q0/PIGGl85ttYSW+UV0IAYpEKYIzFDiit38nmqfU94ji3bzTFCLCODbqinGB4XC49df3WDa+8sS2+qwOXATL3P1E3WoG1qcK5wo+w6eM39SNB0rRiiaLxIy3vXNWuHa3IjrSfFVUPPyOxc2+je0pvtOxYQGFwOcJAm3UiTSpdVmvfcEhbj4A/KIZFKNHKe/ppF+SZoAhEwrfIt9p+JuTP5MLVCFze5dIYuDIhoXNL01wtw6sd1D4ntwluKQa1hu0QIxv3uQ7+fE/GCHmsKBgSayFcdL5C3yMoh5yqoy+zVNBODQ6o4YLiRrn9xEE3vYTRH80MVNY5PQ1+7D5GwWE6Y5ss8efC0BcMaGnYEYlUsV1R/+LgDCcjHWt4UczQT56Zc66VWy8ZKJc23TzaQt8NIqbgr7VH/6FinRYcJIx53rmRZ5GCXt7dx9MSsTAmfbGeYKZg7v9ci6KlnY1BQFszh8SYyRtHxqnr6rkS8EpZY0LDujj3Sc21e+jIk8PVbar6/I5d0b8c6BiR/w+3q5J19gg2FQazd08fn5ahiHGOyOC9r45hii5RPpsiG0ZQLQJyWv6ETyHO+9MNuLDi4H27ARucr3ir5ym5HL2qwddSBTkpIzsYIgeozJjZY7PEfH9NNEmENR779yaEQYk6jklZQonZEo39uyzy1uTnoUy9/liDwssnrLsuXLzMzTAPS6Ou6dENLnNsRd4tdr6iaM16jdZPGeKEAl89UaaqGbtSSNBOf8Y24GxyUJURAn50sPYZLL8Vdcu0NBOShTVpBHhT/5a289Odv4eH9Db0s3XJmqT+zFsRIjI6p4JkvNvptC12HF5fudBVD/z/NCFLcWudkodf+axkwg/RQ9NYTwHQO8Q/dpiKKz06lsj7n55WJM6dHtu/hhtfXL85UzTyInbj/BMgU9C+5vSHz+24y+HfnioJm+6I6IVUbCU+2pVfIayxcLiKysf+krGEuU9FGkLnG8yom55cz2Ux4hSjU/1bgpOXoqPuk5I8Ms5a4z0GS92+rzGFOwDcSQLl95P029T7z4a8cmqA3+OT1u9Q2HvpotYm71VPsjGi0LuwtTdUTfaCT4QusrHHS01YXWoayW2x4ymD6aHhJ3VxVi3sMd5YLH470Jog0xNhTI0dUIEHbJ2xaMR4M46xr97MqzxkIoKwf2VOdDE0OwVrUwbPRugoJVE9GcbxZBI09+m02/DzmFBGUf6gWibNxUd1nPey/0eeFBQCRAL/EWTmBltI+mKnOUaTMZK13Qvx0RaoGNHx/FCbv17ndHY1WeeUG3pYPihZhVi81Xp7lfFlmoYd18spdbv+Tm9Xic8OidyQzUTY/Qe/Gp29YR8WaK3eDcc/cMOJdm4wg2UKzZ4CfsxMdsIAlbbJcMIHuFtRcasrFK4qq1xr5h5Yhoe0+g/Xcum/K6stS1OsK9h3AFsNmFHf+xi90TqSJqNn1i+JjoQSZG5hV1HnLlvVJ1jHdmG9jpOLKge5eVTEbkvabVYmLEQOAbZbJQUrCyZwyE4aeO5s06N11tmgz2bYdHGV38rUaxTwyYdteNp5YR3RTB9U3ZgywXN2X7dhUzbFAiIhh9xG0mSWbyMkUEgHorR7LQkz7uuYEv1b2PIQ3X2PFh7Ftbi052o2empGky3+zGe76zrtgDryOCA60SlNO3IV05fRt/x7Zhb+CgO2ZysJAHGopeobD1cnY5nd3805nubGweHURuGx0Fo5k6vfxscDOQ4LNbCyzXU4rKLmXVhAccW/oDP+vShspOehYMcstw1fFdnvNsyMhvgjnB+aplNAzRODBptjaErR6j5YhXTmqf769JJE2a1LUZrdVcgHs4wMWevhJ9MAEuTMO/rR3rj/h8eNblABWXn0ns2ubyf97EHY6sTsOUhazI/f6cUkk8vFcHmSz4SayVn5vW16DA0k7+PPCBcHYP+ZmE6n1zrl6Q6JZ80LiFixPf7L9E8dTVxzg7pG5Oe6HM/SnAM13TL7msX5n2QV5SmFZrCaaGTFGo6O5JTcDeAojHmqcPqHrOul3/pBmcagikqNQWwo3+Vg03J2VgxPKUs06+He8xmy0n6ydI7bEPc4cLm/cW+n/L5bmmf+Pv5ECCMgSEc63yTI3No3NueudO2EgLBRPBofCgE85tX9iSlamGydahpyot7x37K0QHOaAwHVztfcejM923eyvJLP/Ao2BJ3FsjwJxaJy+N9Eii7o7lTZUIUbzI61hv5S7zVf6LH3USw0EM2GvW6SVi32sFymiOcV8nBqjB6a0+79BIPLzANOqaqeba0jR8RqykDUIQAsHxR5o2KUeDMW9lCa0ShhzSeIVQ7xj+1t6kakuiraXRI43Kx4ZxDCkdIjP4jySn2acG5Ghw1ioMkRdcF/dF7kJ1Dw7c9q4mzKpmQfVX1B/UQydh8T3cBbIYucLZvoVn7/2pMzYPTfNkAuG0djpfufYaRPbgjXnSHZzL7sDqCD+Klr1XfllQ1ki79kLv12oZvD67XZL3qvsxldGBjaFV2QU7xnGvFBXxdqc3u9R2kaAR1YVucTeu8YjMCRcxfyPx/0nQPC2mmDB5C7gjJYfjiIA/oZtJzPV3yNh0hv8tR1ZiQ1/VRKjxoRHIB0WW6Upg8vq+FdGJrJZ+uo93+qo1z3MPIb5lW5KEpOVxdqcwycwKlyr0WH5ackKv/Vo7YKcMXYoL13da3JlQzcZqPx5TW1jH9/qNkOhTDf+ycUQFyYmgsBYHAry4biWzucMYQ1zptM1/KpY7Knp2gurwnYQH98Bc8IU4JU6qdbVTbl2Xewb1QmEm7uT8U6TsJYxAcvXDDwfnK0cXZlPeIfwxpIOUzvAXkES/EfulY4tNkGBmM5MykKB+GxQtayzKlzaRDrM6IeiAN/V51F8ptnXHo1EXSZ96fKI2vX1x9c3W5NhVo/oHzJs39ngAFLAt8khGCC+QZzcr79mpO/lxwlUsBz87Wym3kEWo9wNSy+7si61Et2fiCg9/mfJw7cf07vcHeh2LDVJ7LReqXP+a9Hoh4ukJZgXpPf4AnfwBzyiylgXxRVLC2BndCOyJ/1vBRyFKD3QKyIpx6BlnOvm3IG0sdKXNwATBrMtwCcf7k/SIXTnc2jxo3v5/z1/vu4z3vjnP656U98HUC2OybaX08zjH7kiXLNVdVCtTh6OIz4ogZkS7Lt8vcDbaKl+8MguQTifaETblI40alING1/pdTL00Fe/vYCANrhyRm+8U2SrugOTw3kVxZqZDlkspxZvRkBj8Aw13ySKh+YvU6VJhi17dhcoxykkfVGXmhtTX2+evs8aLdlfI8dlxw6Xcqi+7cfV0H4Y09PraUdtomanmmE7W7ahTTYp8dCsWA97228rjiqaj39YyFhacebTGg1OsB32lLEPGBep5cjhOt+qLeAl6NqLURBrZkM2rcd90VT0xKc8r9W0v3DHkH4C+lgswMSMM9ZHPiB5cGOGc3jzVKJ9dOJDI7swDBYMsMA3F5iolK1oYrfEAVECVQJcfROTv63r47wJWe/NTXld7EI3sUv+aMaW5VOdqbvbx0c4ez8wd30tNpKU3I5tQCVMv3Hzuaw9lO4QpFX4SvvytXaAm9K3Z11kjfFNuX1MSlkqoL2LZ/EMm/YU+dW56jyfMPHj9VO/hsbFQ71B0yN8ImT++37Ox7eSwYTaB+98shg45dOoAUdIGOfVbsNV1XQV3haWCOVylAv5iqHMYclfPKqZB3e5y01AF8I0W1lB2gRUhJTcZ50+h7W3VriBmden8uGSK0YVhilrsNzk/qDTiOJ+3FVhFw720YL8QedZdlGC6oZiewxFlXlN4d9azWR1aotcLY5PLEPwZxHynRGI34EPGThL+GxAegaqFYCo4217HL004c8yHnX2aMrRZgBukZqF2aewtAs6wwCvaekDFAif5DbBLBZpDvAn/TSu1t7xO3Sl3QAMggkv3ySLY1jeKQLLD/UiYeVYQ1pA82oh+loTVSLGBhXLwPefT6M49XaX4Pw5/zDRr1e3QqIb+e7bcZPCOpf+rLYZiZnuZfNrPj+ZpgZ+S+SpccVtxfExS/54vmo4aGjqrny/w02YeFoUzDDu/F3oaTywgO4RVvijZ/vuWthbYnlq+1ZaSQNX+mXNO0RMXJ5ElqrRswmvBVhYZG8KueZyfRFbaRM8eGLS8ZTkfh7UTAx6Evi+fWo28a5yiED0RkDaXhnNu+cYB0RhuM+jUn+obuKwsvfEJIcQFPClXxo0QlVFWd+5zcavnvUZtA6qqB1jH8/fz6KX2yPUfWaKI7G5Us4nT3jm4xPL57AZQd6pS068RNminadUiUGSOmLDVGFuJAaC91TyGEjoTk7+SkhiInuUZbeHmaJuSZtOoCZ1OBVfdkx/XPOZKHYaADqUqM/4TrcjVMpsa1x43GdQby+T35RrlkqXXKFFYWpWabLshQnOWOaqetdTlPwPVzRlq1TeeN1BOwsPGm8l6gfB8+dn3YS4aQgTUYssMaXrtKP6M+mF2R1fYuDNw//ctRJ7Q0w3d/pvgjZhpYdmrJFcROxsg+a9rEAhul8M/BtBLR8tvXp85yFSO6/NzFkh4Nk7W9cxz1Y2WYTJD72lrSiTKE8kEZyH22vJ55
*/