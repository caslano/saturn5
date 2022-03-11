
#ifndef BOOST_CONTRACT_DETAIL_COND_POST_HPP_
#define BOOST_CONTRACT_DETAIL_COND_POST_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_base.hpp>
#include <boost/contract/detail/none.hpp>
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/optional.hpp>
    #include <boost/function.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
#endif

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_COND_POST_DEF_( \
        result_type, result_param, ftor_type, ftor_var, ftor_call) \
    public: \
        template<typename F> \
        void set_post(F const& f) { ftor_var = f; } \
    \
    protected: \
        void check_post(result_type const& result_param) { \
            if(failed()) return; \
            try { if(ftor_var) { ftor_call; } } \
            catch(...) { fail(&boost::contract::postcondition_failure); } \
        } \
    \
    private: \
        boost::function<ftor_type> ftor_var; /* Boost.Func for lambdas, etc. */

/* CODE */

namespace boost { namespace contract { namespace detail {

template<typename VR>
class cond_post : public cond_base { // Non-copyable base.
public:
    explicit cond_post(boost::contract::from from) : cond_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        private: typedef typename boost::mpl::if_<is_optional<VR>,
            boost::optional<typename boost::remove_reference<typename
                    optional_value_type<VR>::type>::type const&> const&
        ,
            VR const&
        >::type r_type;

        BOOST_CONTRACT_DETAIL_COND_POST_DEF_(
            r_type,
            r,
            void (r_type),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r)
        )
    #endif
};

template<>
class cond_post<none> : public cond_base { // Non-copyable base.
public:
    explicit cond_post(boost::contract::from from) : cond_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        BOOST_CONTRACT_DETAIL_COND_POST_DEF_(
            none,
            /* r */ BOOST_PP_EMPTY(),
            void (),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed()
        )
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_post.hpp
tKMI5x01qP+cfpGesl/S2fccCoNaU/ezW9RYPsqqKzV7gulgrR6eYsp8e57grKMxX2ec2lewnHrGhyLsdaprJXdP5F8YxSjKZZI1enqARSM71VRo1oKReU27Yi2blS+aG+3JCZadZyq5qysRrVqJ0uYoTY48oRqRc6gXg1uWi+VLSUDml3b9Up7HD36z4wB9H/wC1Madq8uyR48hC+nSOjYVJ8L1lxnDKZBjOLiYF466nvwdO+nOjZHxLkWU6ZzOy34trIPKMo/oFQuqRCdHAMXM/i9sExCVRtt/hWnsMQbej9w1LI17LC2bMLS+BErrSkAJXARabN/4NjVOTuFjpp8stcMn9SfBgq32sa2l7eNuKtGq5I7f99HzEkrjlG46e7PsZiLX05wiUJI9bj9iv04BfHZe+DayOpPdPEdfVJjGtTpGHc8zTLVLDuOkxHw4D9dPmaqj+iUoCREviU97T8bdK9BGB+34eSGzpEecMs/1ozo1b5g2GlFOSc5XjNAl9hej0KEPEywbxR+B403C7nRTQdRQorjtenLSnL8O7llRsxeMhK+yg/Q111iIePFrloAptjewdMmDmwQ0wbmoifVi2Mtf3tNAQ+MZDuyEtR+Rc7hLk3e9ZqKOeTcf9CxGaa3MV8NwCkLQuzODfBTM1FHsjIDx9T0jXnGkElG9SgiaOACzEQWFs6MTxajqqKsscud2ibfPcHsYGnQ6DHV6mfYfsA+Kefybs770rN3o6Cm+u1T3ZcJn7atBxPsjb5WDNdCaPIuU107kXdEd1kawsTbakustSfYJqnKr+7qvKRjFBfjv70/+QK34ClOFFGP2MW2B78/8PSiOH+TIO4Z/h8tweKnQgxUFsdDm71P+FZ0AtSXd+6TUHp5v/f62YLlLnK/PeGnJVS8c4+SPADBb33NYMMfoastJUFc3SvxQHW3OMvptGlSJ+d5sHe45ylXFWTp9b+2+7ua9/U9A8PPzHPOP6I8062RVKsEmatW1hFiwkNQozsA66k42mf/wNyRz9WftAITAWScTUFwFu/7EWvBLlNaWHmOOoX5MnzLTy3NJP1rHtpgPIkiW+7npUIKjRc497A0FgeLJXeb5r5rOb9hvl9nmNPRunirKHRxVVBBWTxCuoqZHPojVCeIek9n9VZK8PUJalB/k0ejxI5YSRlAAFSzq07yW8SFORHHgievX/krS2rrq2F6iR7mdbz3YLmMIyuJSpAcNS4MEHAQZ0kNGq8+Qju2+Ev4mGKPwR4gPFA7kQv+d4r1ibZgO+afg0sM+TKkJpxriDuKXDxm0ASRCFTcTx3G8ckl1Hpr9iyRioE+qqzNH+uWNdnlkNvSWf749/GV2Kejxwjh0eWHcemlvJa6mLh9wqaUWCSD/KeW63twhgjLfN2+i1mN/3lSZd2nPsWl7ZpOmEbFvrIRzyFnfWG3lkHOKiphn29EjvB/ia3/s1+tVkzm2asVrnqqViP5HGNfwSpgxD8GkEEMEjp6Puh3BaJgWztxUDxtXOoJTh2eCzm/wsZnMhaa7Km4txo3/+MDxISIHaA0hoHKN4OpB6hTTABW5UCTm8tb5EsZ98nio9qJK/jyUPV559fS4x9EGBVm2n4DoCXFU7R7ScNrVzN+6Wx22/1rrrGF9kJ53SQezGB12/rbuXTdjxni9FfRnL4SBp+NssoJbrdSaDuoqOWejP2IuKjMBhsSXKct0i/dNxHTyL7j+PhuvOGEdQIjpnAhYhX4V6tbFpzhfztd4/MtUFrhkZqz+nuYLNtZEBuO29VSEX41Q3uhhFF2TFBZs9ykgDWF/90HUAW2ZHNJJXNzXn27ufgTZ/UhjDBM4vBDhQwAB2m7/8ltcnLvrFZUvVMPDUrC8skNHS/4eNPj5JeiO64KK2qteEfx6IWNgvaWh0WB06JlDVkVObPPkC46lDl5+Teutl25HkZXR1dK8UDzneFsLBnOelxGuFOw/tM+bogmWJpoo7WL4bqkfBWNfstRoTnGK0e514f2tVJ/Th/di4Zh5Yx4ZeZduOQnITCE5ofDFMy1niJhTYVieLt/I/+jS13VPz2LU5RQOqCg9DYFIJ8K6iKJu390Wd9WynGLu5bRW4JS/m+UUlTmBR6AF5mlKP1BFshJiX/RLQ7j5kBNQhpog5Z+QTdIvLdUWgw6biBp4EIRPCsl0S9IO849kcfdZ/8wE/uLa7+vDjlCBeXqcpSCfMol+iEt4/2l7r+Rjazk1N3J/PuRDallC+CbYfeQo9E7GsOngwHkXZ6Gx3KuQkyM5lrZ7EhWVoXU/+OJYXvHJLaw9NerN17NXa7UJarl3n36X/60f33tyIaCv68fV2k7zCwEv4Uf25rSym6eV3AXQ27QWDOLQn0PtY90/r9MYuXSjvNLpzHmZNXnU002Chwm6OSO/c/3UA9Tp7MctxNyKfV3qeIeKwsGiqnCw07iLAczpuRt22yLuT9RvCboDRRhn2SMejIX1QvkxLfA4wzlG3DX2IevgnYuS4aOBEB0RHXFpUskShZyXyYyp15GOUizXyNLMA6uixRpiDV916+1ETr6uGyLaVwhQ4KkMvzrTFBXsAwPB8H6maFf6a6zchfT6C9KPSQiKKql5C6mlxrsi6L8s/fE87bqT154J839XUfS+upzA3ldoJB92DixUEqfPw6DgVHfDZIw5WvnnY2//S44pajbZ+ytT7V17b8EyfevKHvIxdHR74i5AiTcSy4ML0EzP+GtoDkNfFHVw0wq8erfu23pL1yo+UMCyTz9ncu7OM3wpxtLhyJbySc9JPtpEsv/eX1ba9o7IHkh923cnQmXH4cxlF7JMZVdBTNVR9tbkIsGWIZ0vMIe+ZK0Q2j+tNN93M1ysxenPOCm9lo7I3zo6jnvFaFOJRhwcjM0PyvA5aPpG4cKujrSnIWYmuHR9snaLf4p4qeMBYmxqw8LzQmeu2ZT9rRuy4MGJmc8nk8vN9hoKIuLa5tw1LvGB6PLh/WfRWbiRWv72uuw0CUg7fo6mHTZNO6w5jtEbq36fU6iC4H5PhPdPxRcdUxRa3zFYl2S/pPx0TJRUJRs+JhS4ILr229qFh0MnPjDEiWutPcRb/XJqe0MXghU3pdduSActibslDtefTNme5I1NyWOkfiO7GPnqOPmwBp2GlTtahk9ZMBj0d2Z4l/Wsnd96j/ZLrVUkX4CJ521qwmK9LQMt/e808/63JDiM9zm6PlA22N2zEwmF84XjwQ3wQ6YLirC+099u9yPWmd87DfMtCRYCUxJUjL53g3pB+MLoGm3OwJpOQFqlVaoO8p8A5Ab43lFo06t1qv8HMxGIE/UiAIBDS3VdS5LjOJK9yxyg4wzVOVVm02aVVtYZXTk2OypJSSzxo+EnUqXL1kabuUCuYjHw/3MoehOB90BSIAg4HIDDPZgye2yjTyAZbfN2mG093Krmxo6d1gttntekbH7HM7+FDfCt7S9lSjaXYdFa7I0jcfh7FBTfVYaU/CJMhTQzzHaaZZJrywzOz+TyK9YBdJRSqxtGpTTWx28dhX7yQUIhgnpdgViNkZKJ1wThlQruj0Xs5LcQ9l4Jv4r3dZ8bufaMGuZVPjg7r8T5sa/QRJQsjTcKx9S4Tz10XGXJ3em9q+5mw4J0+wblOHZDK8MTyRcjl2b395TB/+UXaIenZueT0N6KTvP+xicSnCllXlK4VWJWGzRu5/7QS/jbUHeRdJX3dt7Hqjk5Y6PLrYcRmYD2uX4ofcPnwwW6eUVJF/0lJjYFl+nfinjrD9ise2pB2Ci4v2yY5jNqGcubTFaATD+zW8z7Ex36/jNd/WLRgoYyO+f1gup3bXBADHf78pZBq0VBKe/QtcvsThWUNF+Hmf3wde/4XsDmIt6pTZlRd9FgxN81tEOe+mIn6rdv5JTZmoK4CH1xJJLP1XtnHA9N7AEVtKMNueDSfj9JvQjEIRgpY+y45msiDBQBWDpyJViUTYLl63OG94fLUm/2EaWS9NRMKSNt0zFMPy34A4XmRqE9XwCVYfeyV8uKNxrE1mS3H1RNXJfHKmqJt/nKav82t9FuKO17/XGFbT7cZnIP21iPnIuYw1bHOBTD25zS3fT2H+VJrh8I9eMUA0laSS/oXESwpX0J/oZHa27XZqqO+wTl5SpMemPFqezOQX9RztULw7oN/8m5NwNd3hh0Ih5R3rBuR8Y1Q32V91QkPiHRu1tTpKCzZvZL9ZO9eEBr43U63hv5Ja4jheUUP7GhMldGvalBBbMwpaNNbVHJOVYVXqo9kE5JoJUl5LTdAb2GQw5Yaz5njs1f6/Y4/Nus5hBdKrLeZnWF9CVnvcGLbB+8xZMqwtzmd5V02x37qWoInIGulpQip+zY167D/NSgh7nfGlREmHm+Kps8BLMWSdX2bukKGeLJItH5a84LCBWCH/xq1eCcgdvWqly5WymOFUCnwuDFKXD2m2k+VXBHOoaR61za6ctvX372dkDhsEA8Ce5pBkh+S1++/PaUUR2bjxyNmPfza5UTvXeuZx3C2ITGVib89gJfEVhF0cblzjr1L5D91CALV7mOY4660PF4KFqn3yzdU4wosNIA4MVZ27Zt2/aetW2bZ23btm3btm3bd//734cvmYe2adKHmSaTtlMUm1gEqbccAilOY6TzW3cTB3jqxHQ6zEabx351oJk/daFbQJWluB+P5lj8OEHaFbHHKfaWUlp0TgsSvrUnhx+IHnjaxxZZzeDMceVDN3y++G/PtNBG72uHzkd5hrXvQY82bhHyBNDg+uY7R5kxR4ZW7uUKs8UJlKyRWmTIfvlnlEFr52ElyuesKvb0NMF0cvFcsjgFJ56gZw39jT/0Zn93HGruFHfqWHaPNMIH+3rn3a1M2rpDUhzPsLM737FHPtPSWht0HFSLizZIR5JKyU/nmJKGp4nEfHi1riRuCbByVo+8kUT9E9bMoLY0fI/fNvmrlH+ZHzWMp0d9huk9WHWFZCDFuqT3gDNudrmNuUr4xP7LXMdDuJzy0XwnC9nyBy9B90HBTjvIH1nCS1JIm3o4hUEbJwgZfGcdgtwDyjmZSwRn9zJzlIG0YVd82zn6GHyic5SHk3eY4xK21Y0S27EFtPsxS9zCpztjs63hapVFjs6IsxmgfESUkiTwo2zgEY3pF5sNWJyNSsGPIhZfRkSQjp6MS+BW3KpaSlwbGipprtswx/N0zPus6cYTD0KLCRCteOPXKNVpXV/RUo/fVSl9T5FX9SxAiXYa5Qe9Fean/JapP+wP01Gv6WNCTBhSrtfE5avBLaH63lbOZ9n7u+0Lo5bbUCdHoPoJOw4cMvg+pRJqU89T/WFmCYbcRh4Scb2zg+np2Eq1D9BaKTLK2R+OTH8EajgcmD/X1BXQHr8E9XxSjzg2Jm5+qsrcUDdMjQ9ZBMzeA5LrYsc92HISQz0GidQCLxMUwrV8Gvy+DpXLtckoOzVw4BVwHhAZMa7Rxr9Uf6qLJGlzUUK6IhCcosOoO/I86AsmfXX+NXt389vs0SH/7U7ids+E3ZQui0+EQcsO2lCc2AdO/BnKsecsUsU3A/UPvLSkC7mu5zbCU2BKs3ieytEIxT5EoNCrlU0BXibX3BbTB2/3/sef0PIKFTHoe1pr1NRIihiDiipNmjqhAcph6hMbUPWYi0dKIeUB46Odh+uSoasw722M+ao7ofFAtjow/q5GWgZcPNUZ0/e0ujbNaagDH7otiwwjrCLlP5BeAy8FLgCoyC/LxiDi4L/ZH8PjdDrqdhGS5/4W+hSOwmnCJdtJig4MTE+Fan3uUhVYpFHhOG5RpsHPxbrT2607ZzSDelgyHg3z+aJBY97x+al23Y0j9zpbB3YmfffgxLKDaWpUKScEddLWYxfs+VYGHi6EvKEVDooUY/WBukmPk2GLq+k3P5L/541O7xCjzwv8NIGAh7yktcSa+K82ulxxEhIiXLJPXQ4xKT1v8VjKZSo+UyPqROoldqpaeUutI5mI4/EqpKstHvJkkEuu1z8A0lBL15uYMz/uQT3val/Ffz2kX5VuZIxxJ4FlZZOHMqr5vO/ZeGlFaN9AWRl+LJXx0zsf8Tr2GU879yedtkIta5Nfq40ac9YnYac3NGoaDBYf9LsmQI34/ilFGwfg0EqH9mfs3Hr/SFU6o92IAEBBtfJ7FsIWQWyLyHvnOtbnr1Vru+VBrWhD9wx5W8H5jdL4Uv0v4J/yjpltz5Ifcod44CxdMWs9s0vA4YxHhwmD6dEhaB0va+eMYYcN78fB1Ansyb2xt7cqoLm6mjpFsEU+pQDHIqZoLX4y0xnSt9RLnHt8nQ9r6m/X4O86Od+WTF9pA9dCqKk2gJ48GAFVgzNNZZ3s1G+9WywT+8pN3O7RzpI7SUUy6W4Q9FZeBnL18bqKUW0VTF0cPv4o9FAR10jcXBx5c/rHwvnQfUoZwGF3PsJHSZ3GMoe5NJgTmdHw+CdifnQVINkAM5cYuzeeDSXPK+ki5IGkdhN2r6FWAYFWNuDsNzFuOXrP5mUt7gfddUAU1RXzQWe1YIMmo8rFJoLTNP4LM7HxgSGIMrspOi2T/IaGcD5LiFfUI2dJIezwJPfbvz/TW/mnYq67CyiPl0jr6L0EawdPYZ7aDOpzv6RgesX+/HBfa0kXiOmQQF7N9hkVBneUqN9lRnL5qkaL9W2Xl06y7B1af1udKYv1Pdpq1X4pJL0KUz1mM6yuuwTaro40TxNnyMQshl4ZHFAfkp+1dQATLCWZwus6/icqSgeaVPEL8UHM0aLrUxYAN9w/M1uBt1//847nR7HSBqlYZNhHw7pjrnRCsDjr7kKJEUQCFxvDjCkiKKmA4/J9az6plARSmGqAWCMNcE6y9ZlasDKSDjlDOdOZH40SqTN/XdPi9HED+uF6KsuQ464nvzPJJWRchEAhFDrA9cavY2ZogdM0sfHdCUH4eJ0MCyqUvQCfMd+pREwKkuc5X8ArwrkICJuVTHh/wH0fyUEw6ob5e8AN6dDPMJ53bhYPCULLjTR+W2TTu0UXrVgaXiUD/aNKeN4DiTn8b2XavKqGJVTJYJ9H0T1zlERJ/T+5fKPbPv3V/SU2ryQY40EAxIR5sfLQHOi+R9N/Ejxpe2unXJveddG9WVNPBaJmwa9qj+vc2kaHfLTiWEQ1g6d/KIn9tRz+8TdMj41aE6XE7qQXrPyjp7+wB5KuigJZwRddooyoXbISGTVKsT58EOZ/xS7Kr8VMvV4NDMyePWPtC5re4MeRm0qOVoY4GDKgH57UtJvUKrYd8AllUM8HT/4ZIU0GBHkbQRx8APPTihnz3VZYfLQE6HgRrlg0rRgrY1xzFs1BLYxYPnPS2n2SddQSHn5Bw/alAF+3P7WjSxkrzIWSnR4LZW5xs99aOPfco1X21HFPKXqTLQD2qa3jYHHdVDGw0d4jIOKYgXDTPuZrl0LEWPC40duP1crBsoId6RSu8DqTmOo718SQfwy0wHpR/7v1beSkj4EGCXjr9QUftWpXlAUl59kyQTRsa3y01XUBibWHjgQMWBYQgoKbN6gKsZmR3B/YnvEioac/F6GPyZnqx8LUR5XocAZ38zp2zZSbf8zmq4M7wguzM1ntYRfdD6xZk1cHzR0A30cGb0VKjMz9DU8YqSLHIezCr70fEUFmB5YAju0QmD1jHyf2NCRF++B2SsaySqCNcx8My4qWitHRqSixKSyljLzm2OdZEyHS8oaMHBIoizZ15SNBRDVHH29P/OyTfkuLe6PPEM/OexqCFmboYt8H8+hNlmG6tFjLxk/tCoRNM9sDmC3z14vHV1p6vDdjZScIdc/qIcsurWHexeaxCrx62vwmb8IPli7eKfJ9ZTsbLZAY222HBk9BHg+XZa8l3d+1QI9VLuoliqjgplPK+MUnAo5+GMlcexftDy8yosMUUCvhxbGaS0SmEeD0n/LPiVBQiGgYkrBueYDOF5akbQoyJ6rDJkLsZNLuf2q6Q9nIs5aFHWGo/gtDoiTBsBDvdPeAXwtSgt2MIrXJuZN+zXqrjUylQBMeDeJXHCMyutAJA/9AykdWGcNs7FTovBrx+hxrvCF4VOkhtdF6rs65BhK5K2ArZjuWKbdlOsVNU5EWuh9rsm34jfWVndDvSa+0ZUfJTviT+wrOiTALag2ZChVEV+8JqK6EX9lgj5YGli2NYgNSy7rP5K2hKA7AXbcUvUhFWzXz7cZXWYSD8F2QmAiGFAuZiyhQJuUS5eZQVx4M2YsFyffQe5Y9igqQz/JaYanIhQloVI1pojrncTJQTOX+mKxbQaURnawUcxSnW8nGvE+345y0LREBgdL9BbFBijaGlOIDPikUaNkamuSuwMYb36cp9kZvLnZS7XmuPnBMvNXJCgUaf0Zg3VkgQjI+CCbGbTbyIkFPXmflY3a2cgGf1YrlsV8RQS7ggvmJQC/5GOfPWQPTmt22nugorN76p4neYZtg0v+g8H6d0POdbXraCFpkbaF74KqKK/AVv8D4c5QbuS30Obl8hc/2vMGisr1t0DXbPYGVY+akPh7bYvqOUrwvWTBCR+ZscNDjZtkKJwi/3i9QtCNOWwS+Obo2YCui7Uks4FqxfHvDg5tPDI3Vi9MG+eDcfl176cO8FKvMSNUct7hsAF7ch0PT8HPABNBVsWS2Xh6FYGLO3e2bwBQq6Q2H9jMpDs8coiPwRzx5trJJEahjWTsCh0M8cvMqp/BiXQgpp19PsPHdwrQrUpMt1EtJ/DnnAi5t03ChbnI7+jJxP0IbiwA8xstOm+oIOobKHHJGipQwb8Zo2eeC+xXYSqCp8F7jryuul96bhVvQZGyx/2fYIQZEpQrnXcQIVy8WI9QNHeGSLd3rqKHvwxIWgVVeBMIiWh+hJgFkld15uUIvq+Mcvqcm7qxaqDsVYgsHtHyFsSDS3AhIh62lnxVmrYjLH1n5YUIHpN2sFyprDrI+bYfqGOehNas8fIuAvuPC7pIo+ZY60CFnagJ75c9zuI6bt5Y0HAmiZzxiYRfy6j+QQYzCqc5gKFzkzuQmj07mxWDLJAjXsuH0NPqF2WglviRVUeU3yavqTIEVSIMicPq3JA6s9zSVcpxrQpuaSEUzZ+olh2vrEJ47PrE9IjAb+RTIn4YLtgrzDyZjpf9wk0ug8EN2M5oSfFqdatHlb8MNafYqPiSJ3XauXjAcE4m9s8qWfOn4fu43KnpE+kx7+mk=
*/