/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/make_dense_output.hpp

 [begin_description]
 Factory function to simplify the creation of dense output steppers from error steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {


// default template for the dense output
template< class Stepper > struct get_dense_output { };



// default dense output factory
template< class Stepper , class DenseOutput >
struct dense_output_factory
{
    DenseOutput operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            const Stepper &stepper )
    {
        return DenseOutput( abs_error , rel_error , stepper );
    }

    DenseOutput operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            typename Stepper::time_type max_dt ,
            const Stepper &stepper )
    {
        return DenseOutput( abs_error , rel_error , max_dt , stepper );
    }
};



namespace result_of
{
    template< class Stepper >
    struct make_dense_output
    {
        typedef typename get_dense_output< Stepper >::type type;
    };
}



template< class Stepper >
typename result_of::make_dense_output< Stepper >::type make_dense_output(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        const Stepper &stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_dense_output< stepper_type >::type dense_output_type;
    typedef dense_output_factory< stepper_type , dense_output_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , stepper );
}


template< class Stepper >
typename result_of::make_dense_output< Stepper >::type make_dense_output(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        typename Stepper::time_type max_dt ,
        const Stepper &stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_dense_output< stepper_type >::type dense_output_type;
    typedef dense_output_factory< stepper_type , dense_output_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , max_dt, stepper );
}


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED

/* make_dense_output.hpp
XmaKWqHqzChrt1WUZQYriTdIFJGtG4QJxyB9+y+tsJ7im+jct6Ex2qcdN/jgzfTXv4soxqcWtuJdvZ1xihFHoDbKOPyAMnekjAeiXQ3r4DLaywEFmiTDX1I6JTN89Fciw1YWKy5zcGI/NtDMuoXy9IdzzNrpo6XzjNG89lS0PVmZuIe8svtq0LQHYSCzMND0ueQpsdRJBXiMgFxzDQTed5VTcd/ZW3FX4q7qi/kOz7w+ijuB+2Xc+W7MeS7F/X48u/DciDhNuN/C7cAccjX85+G+A/cDuB/HvR/3u7hzEWco7itwj0HcabhvwL0EZbQh70HIT8H9gpM87jDrMHnZhp3bZcedlUVXdk6mv0NwvHT1cQ1z96Wj33nDhnn6DxswMH+QEYn8rpkAfO9z/7/+O66mwgIMhT3kydyvlcN5YrVqwSwtVMzBU6eSaZFv77cNHSjfeKVlw7/7OYOkKLq1Dl7p8NEM/44R7uwhl17wlvTvfUa59CgjVZ8ecumLkCqgv5udkj27e8ies4xs+/aQPb/7JhOuUyCVG2AGURYtJNFP/4yj0+jWKtXy9xUvC/3VRG7mu72f1tb8lr2kremJ2Vnu5resJc1ko09rnwni+6d2MdJWqEypVlArvxm7ECqU+t3UKYlT4eJYWfhp8qnPPMaBbOoZoW6yM7+XbFAxCQWyOGTKIeW7WvRhqQodkdxEkcksobd97lRa/uukLIXD9PwWtY8lS6iZgzBzdQC8apXhlJdhpHVqORMVIHPVBR3N7tAAeazDja2WAb/ZVWF9r4lEM79logVPBoVdHc3WUC7Cs7K3WgkJzwdoxsEQu+zZShUChctaVX+lyDS3o9khfCqqKEWc/ze0T0B9Lzez9fUXXzf0bKGRQrUSq1L1G8XMYIffedC1BbQKd3Iv3o1phDz82ftXjy8Mipnebd46jXG7aZRYc7TAcLHK8ju0HReSmZ+IP5s4RVzbEZ2l8EQSRQghTyu41tIt/9498w8EzU+z8iByYT4gpEehXkH9xlOimvDkIdyBJP7kd69ZT77Jz9UMDGoV43AGMFCQHzmWDE+AVj3yJONZw6W1SlDfgukXUZlBIW9EF8mSe2EoqR3WPyOm52JtF6faakjhWIq8tB1/YVsST5GV+Th2UKvgB/AFklrrDguoTU7vdHu+VLU/HIxvpeFAUP/9SaORw1cF9ZMd5svEgL71uPlSGtDHIpppYMoseOF9cZJKH7oWJet+nyoZCzwSyLmPIPKAePXRPimtBfukfuVrgipb1/GNlzQmr0Jt+B3PK+pPkTtfniXKU79jpg7oJ2TCmEgIAn6drQJDs45j0n/LI3+ZgazAX2R1EWSP94p5Ya6JKdfaCBEwo5gdd4Q/slupVQKxGcX67KSBMWekSRdIrxbnxcPP9Ogvu1WF6FaRrmT4wjzUg/2+QJw1zJ+kIkuAcfI7qoqtoScjq4ttYWdGPnmsfmtVMceXc69Tt/qZ3aMHneBs/mpJBuxXAIqP2oFaxQQBkJsFnX28/TAnT4yVcwPY/f4uR1wuf19BkNBWNVDeGgz49adfo0o/qD/3WkrZH0cQx+Gg/ozwRMrVq4R5TyCobzLjrb5ZPeIySYZye/sh5HQYYaCO6Wb0+lT0y7kcGn9zQcgjB6TALP1ncpWg6YkLIIh+htiLiblX+6Bh5sPpuKxDzXFnFBTQN6KkoN5HZO3RdkJLPr8FysqFf8uonL5A53ZLmJ0aZ+OjpCSb5TDs9OAWyFjTG5Zu4sXOxsd00PLn6NcTOWW/U8RG7k7MQMhSrN9DWc16dsLWrGfhRCt0lgk1pIalOMeY63DtgPYS7Guaf50f7RufpWjPNre7o7kwuxFnYmA=
*/