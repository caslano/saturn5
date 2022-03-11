/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sink.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * The header contains an interface declaration for all sinks. This interface is used by the
 * logging core to feed log records to sinks.
 */

#ifndef BOOST_LOG_SINKS_SINK_HPP_INCLUDED_
#define BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! A base class for a logging sink frontend
class BOOST_LOG_NO_VTABLE sink
{
public:
    //! An exception handler type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

private:
    //! The flag indicates that the sink passes log records across thread boundaries
    const bool m_cross_thread;

public:
    /*!
     * Default constructor
     */
    explicit sink(bool cross_thread) : m_cross_thread(cross_thread)
    {
    }

    /*!
     * Virtual destructor
     */
    virtual ~sink() {}

    /*!
     * The method returns \c true if no filter is set or the attribute values pass the filter
     *
     * \param attributes A set of attribute values of a logging record
     */
    virtual bool will_consume(attribute_value_set const& attributes) = 0;

    /*!
     * The method puts logging record to the sink
     *
     * \param rec Logging record to consume
     */
    virtual void consume(record_view const& rec) = 0;

    /*!
     * The method attempts to put logging record to the sink. The method may be used by the
     * core in order to determine the most efficient order of sinks to feed records to in
     * case of heavy contention. Sink implementations may implement try/backoff logic in
     * order to improve overall logging throughput.
     *
     * \param rec Logging record to consume
     * \return \c true, if the record was consumed, \c false, if not.
     */
    virtual bool try_consume(record_view const& rec)
    {
        consume(rec);
        return true;
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    virtual void flush() = 0;

    /*!
     * The method indicates that the sink passes log records between different threads. This information is
     * needed by the logging core to detach log records from all thread-specific resources before passing it
     * to the sink.
     */
    bool is_cross_thread() const BOOST_NOEXCEPT { return m_cross_thread; }

    BOOST_DELETED_FUNCTION(sink(sink const&))
    BOOST_DELETED_FUNCTION(sink& operator= (sink const&))
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

/* sink.hpp
2FNb/DdTP4Aws6AuFy4nZ2F6026SBU3EQJvMFL4D+9nhggzAIRXwolG0Vd6unfu9ZUbvRaEmIF+TWwgo4FoCL3DfPe9hnbWps8+/3C6HPZmhnyY/XL+1vI958ZULLfQaNiyjwBIBpVD9bulTmII5WYSv4euCK/tPJglbSmOaNetMmVeywsjHDl82LMCdQUxuc4z3a+V5fkH5yDlkx9Zjk7HZvjd3r8ET64AEoa2hIQF7amTgoeul6gbhb4tiiYk1kozyo4K3heTVbvMGXZuoxaae1UL6nXzTQTQWLnVnftuCYu+uyyaWvoW4DjcuKmNKKClOHc4rV9e9n9osgxHc3Rx18xfN2NhkQqLsB9qLR/b55T/NgJZel7KKLxcUMuDMI+hNpQmUvhIv/Z7Vma3n+to+eelfqrI7EtIYhc85m2zRhgW9oEJxo5yw5dk0nrOnSHtEqa5AxfNgi/+F17d09MMau4zHXH2Lw8ZOGokch/mc2I1gUxGu9J39ujy1c6SEj+rMjbwWl1VIgxmbrNlRUyni9jlmyqiVXkM+C/bNx6FI2ZinJP5/nD332zqL1Ub2PFHeu4GJZqhsiH19OcYCKtNVHONpZ1aYUZKzTFboKgrpDE/3Y/r1cWaPlp/wYm+7oEIms/MpddFiVppTH7ZrAZxpmc9cz8Xa3TFL2l0Wjy+4joG/Pyq53XUeq9tTDm8llApMToVivl2C7dAbu+izJc3mpEgszTNDl6NREQb673XCl2ewwnD3ZEdqJiO9pPSUKS/xZmzZwnUacOv8RdbopXlZENaucR3tJhPSqzTQpBB7YBoMQC363b2yJ9XGcmT0lub7Hx7uk0aXxCGv01KxxsC29kUQ6nO3FeyrHTIQhRG9kUTia47LOu1ukXTuk8s85M0an0ggfalzZffoETmTHyP/SZI68/pW8GGhagEb45o9vCUrZ1Ft81xKDUsRQzXixEDKg/lk1eRA8mM8p86S6hExZASFvvFe9vxbd/yBJW0oN8VhinZzCp/Kxa8JVcDLQERHYK9PWlfD+eSExwOzmbaLM2SdFKZ95VR2JvCrTEn0bqZiq96+bcFrdybUntBE8m1iB6JkWp5UrMS4btpOyqmLmBvTZLYwGa1xvPXTyMuJRg0FIsBBg1ynBDVbiGETK/xuS8u8Yc1ll+GJXZSPIrFalNb57RocQuvFDytxyPmGcs5Wm822bD4ZqcF5NPsOLF7dK5X+k4432b2qa8FTKWQEEiNrNS+7p/xWIEAjma9SGMrciTbaeXn8zC3eouFn4M2xmU6mu4BH4AatSTu+u9aKOLyL8qd8KEUlK2giT5u3veYZ9nqYa/WlenuWaxg4Rg3E/QRJWFwGwKI1rK+5p9R3kMK76TX5RbJnsQM37T+tJEJ7R4CkVxlzeToogORYeHGWQjoCRtRaNZZybhs+yH1HSOxR7S9sdTgmU3/oAatj37WbWd/v2R5tqgTU0atbbVQyC+u46lqpx+XgAoghE3onGAsCMrn4BqRL6AUWS5s3wxKjBzx6v27Rgqm0qzypFCSIt5HrPa8fmc9z1GfbdA7Su71pat1cXX9Sw2ld3iKtZhOLq9tazT9rbqPTzyaOrWqbHMddAL3PLr3zLshr1IiHNol6o57ARAfZQ4JYf7vmEVrAaegjIm1r39wuFSV3Yp0UNUa08toCPTs0XNVzA/bkFDrpeZvGDw9sVoMzwvcwCAA2Nub1kPapFUk/GXepgrZsKTKoNxrZn3cGQsYXFPLC5D+YYlnJqyusU9wvzlKHKl9WMWox+Uw7j3o5x+hliX4d8jDsOuMv3yikIlKMfZEUj83uYpPiLJHeitTTvx812LuWblEfngBZmWXeU3nvtthvSPwpQmI5sjFefFyHS5VQ9pNlfviJotdR5PtRdTbL0nNctbPLhfrodl009ADhAlV0Yzjnsmt9vL491dBVzfNnXesCfUHDncR9L1u9SLhXpI7fYKo/5IWmD3ns7+mdQehrJzlpzRYDQ7GYu/fw4Z6i9DWTI3uYh0jn8zxNevjnpf7cw/sOtH5IHjs8hmk7LhQo93pVfcMxT8076xBf3dDksKww8N6284KeAo9AT1/IXptgCHdCtIuCEy+yvu/dSNjINhZiP439+gdYdFE6PlvpqQktonumVoEgqc1VTMap1GsSALTkAH2UHWCbSK2FS69ldWKYw03zazfaa+jl6FzbFC/OXmHuIauZxcg8pVKXye9ET7kP1cTB6N8sWKdXo2ELA2/bpEbDDsJbJqfkXaH5tyzT4CAgBWOvRh6TlCpfI6Rt7xDAUiTCVXY3YHTmquEhy3vxZ7CQd8AKiscT7W/aVupu5SsQd/4s07RqDGEB9hnw0x0UteOugKpzPzqZV8UAXpqJN36ch8uCT0ccCUWEB0leEa93TQsj/g4BpLlc2hYXjWIxTdpq1/JQz6J4+QFY56rvTepq6GgO/Wl0wCo5E3l9flzzZM+7p3U999MrnIwhK6Q0kX2LuXN9Kk27SAJ+8fe2dPt47vqlTfqJbyC6HnaEfd4OtGSbWMVGYiGPh89JfSxtKuLXr511V3QjCSzsrLMUFtZ+dbGs/kBeqXv8nfjz5NM6k0OYG570LWd9XCgPhWP5zJ52pDWkhJ/Hb+5OA2htyX10Zh3uutQzpwH5Kl6s8M4qlYzExL0VIEPN+tsq4wJo/+hu202RYNHrRwczS26LOQRDDlmrkLUGQ/rpQiJzYx9zsSejJGdPMPC3d2Yw8xg58JD73RmlabKrc1dkDd19LSJb65N90ivvykP9f7hGwdv5jAOdMf4hMR9EnteDCexBJuSrLI9ikhArRBQFWPMmOqbnxTE8uulHlaBm0UV8xHjruSrMKYj6OrH+X8iN/+v7XNtn2T7P9n227bNsn2f7Ptvv3yn6LgD/UwHa/2g1qN8T+8c5fQMABf2gNOce/9t+mcHO9n20t1pu4DEGrJ+JjiLBc8NWSBKmXZLvg8DnAzKIIznFpimOQjaCuAZvz+jaEAe5HejXRPh6HPbcWSnM73GfNBZdX6aQlCG4zXmgWFeaWy55vFcp1yWwsNrX2IUM3K/GPRpvvHtVaSmyMXyBz4HTzdTY6IC0Ju7j2HbPfgIRVf8gjDMDOjtDogr1pWzk8unn4oUDr7hV36sk9vNg69fwmFraWCdktucvaHExJ7V2uZy5HSntvA8ZnaU5qLR6xXHpvf9p8TFkN75yTrYyKRVkzXYGL/5l/o5Pa8hcSs1bin6WUQLIN6YfX7q5IJubvVd4deBOgf3HTzFbhGz7CoTIccNrI6/dw0/3hR+0Cl59e6bdootdPqE7ho4c7j52kbNf/M/7AdcikluABeWO8r/vP2p3QZ+Lmsmj9sEnKKG+iqg8iO2UanZGsG38gElRowuTIU91ZL07Sl/8cfrnK270UG5uddTlr2SdZNTTyxh2V2Rh3/D3PA6jGGEk3SXz4wzAoT9OztqPByWVw2NPUi+0btmr7NjqmRZkbXnP7YNqvHve9j/Xxv+Ag/XvafF+5MMvzSROX/yRdSUBdWuVEcOPpPdnsQAehXwOAGkdGS9wQ5DiDCmT+uQRNRoZUK79UwNgaD2Uh+4Yy//Y9pb9q0e8Okn5q+RfqkWKVBI0id9bi1ncwEFtllKWwIMv/6blal8ydbG4K/8OqtgOzEHzT4mnUM+ST6D1Omiq6i0ZGRaTvmilwLMYJPDnp3nLnlzURM/MW2ftMmlhDWmmpW2LeauHDNb/BBBtTGBWWP6fEgcE/j31YD4Pr7eYeutK1DhIGY5K1kIpKV/OMMVOfc+vKh4fBPUEuc/rd1O37KCviks1X1vkb3byGvHg441ANz3skwky+awBpYbuZ9+deMPj0bWKhMUWOBr/BIeyb8/MwkjGTk6IlBiIm7vZkt/Zo7MkVLPNvpOnM8TN3/USmjXhwtpC69ywJCSy0DZLJ1N/zRes1Lmxe/xVV9LQsPtjZQsVLzD90XAT71m9SBNiK0zJHL33hursflxhvwpinzJUCuplTLEqhDIAKzKZ1UNJMvi7lc5WMFevnaJ1DMb+qNNrtPKSj32SgleOj/KOT19+cBo4+2D24kP2/eq2RXZeKHJduEGg8FWlvITMFxQjQJPTEGnQaRMT+UMIbCYRh5f/nXbjm5f14hApR4yLfuX7L34f4L/YbTRx3ZKsHOMl6kEpEtUumSZNo0312103m6jmy3jzwQAfARN4M0aOjj9CCD97G4ksbZt7gU/tyUl7n+xzfnElxPn1dI+0Dx/kWJlzM+lndm/oeLBFv6iYzaPDdkRuHtFyXwd9UO924fo4eQ+7GvIc9aRxykOwX7ReokX4GPoPkLZ8uuMJKOjNGQl8MGHsOwNn3oXHAy5emVFmaHHERFHWZrPLbc/GkFSDpQjjeSdQH4u/fwyxAxZe/Nr0eKXKgeEPZV1CZsfIMGuQkjAqLWmv31sSqbmIbIWEtBI9Ui9fnAihpU/A9Ev+e/6Oh3cNDijoz8hZ7FGX8BsiV3rQMZAkmdDnC+XfLykrOhYxHJlEqLWfH6GbjOn/UTf664C8CtgbL/8/K1o8NmBceq7b2alNL3Vn5JbX4+IOTq+upQY5dTvc1RsJL3OOJijlnHTC9KW553Nxg0kymVNqXtlmM/8xZzkNyzi3z0O+GyFl+TpKzx/N/xi0b8ock7OH/Y3mMzePUjaXQNg79NzL/uNTxi1wD0+nH+S05/pdG6cH5Ni3E1funvLq/P9P2gZvbQMt/Po2pWyll9pSroztOuhmaFIupM8Vsr+n60HNEyvbhijl+ySWcvw01w27b4rDwbeUwYaNOmZLuXZf9+SLexXt6tS/nl6Pws2gtcR+1P269oMS/N14EwuUm3v8mli9qflGpA715ZuKb42O+TW3UkcPB6ddY6ePhhxYOku28P+MmLqZQ6Fe35X7HoVoVbxFox7WtdLGH1mxxa7aXqYBZa6ku09a9lFzt89clnELSg6BJcbywR4zxgf0LQz1ifR28uyr9JjIz90nUjVzvfZD/reof79OeyTFQ3xY3tjvoqolJU4P5l5U5n2kb8l5ecYfR+2EvXQdRTc3jdrOpEhCTPRKPwBJ+ZSSopQLf+1+QKycKl5fwYhZ42iZk3uoxHLyMinwYCkffsInghvahkcpM7paj+qcOnuvs5ZnfoLuDwTtZEvY5d5Lv7TPxH4/smt8htiiLpx0k5RbD38fJ0TOsfT5eGh3M4J/pxKttqq2rEy0vGJPBMXm5KCz7v/c43v5fvJbd0bKT7rHektMFUvUGw6mFLY+tY8WGSchetNLMNFWft8R7+tTGcNkOlXv2irr9dX05Nv1o88wOw7LI6C2LuqVd+qI9sbo5zA3/wDum1U98f3c+kfa/xoKWeVv7VfYLipf2T3fyo2t/mt88Hq/9brOM2qZhcNWHxUvi6bkOvWU9NMctAvzj4qj99mVzQYgaF/JpwcLj3dzI6oLJrhSFgss8ZzUZWlvlk/reDnlHjLLl7acORod4E35wB4tT7+8GylbY3PyGNsEY4Wv2Iccw/d7dPoH7it3UPF2frXlJ7nYuuagSSTOunKaTDFM+jjyf/xqvOntVdsH28hiiLTd9upOQUwvhS3B9fvl20vR3EvI/cH/HZ2PGUq6fhWzyFbxdP2jYCDRe6+S/mcbb2Nbmp9bXYTJ+t69c69s+zf/5jcyBOP02vzq1UwpIRorbKLyvkdkb9c2eoq5AQW/m7LWwQuICKRza/3pbNHdYFvPp65exWFCwaS2In0nd/VzpJPyQ473OlDfcX7CT7Uv/MUQ7mP1vdJ/s4PfY5BL+1Q42u3flPPYH3xfuSHlI6PdMS9PA1avp9BzIIsJP/j79+Mh2iUl/EHsq/SLDs8GarY0cnV+8YcLXiM4aH8YfPMusMVr6l9UyDfD9c3+LUCYT45Z+gvRAR8kt0yL/K77G7hOv85EoCH4zmL93x/e2Trew6wGH5vaU2ExA3N4McCv88cIegkJz/e+ErxSAcHB/qOh3m9quJDs7B9eLXyI4ZyZZGQtcgOZ61g7JyM4aiXEaZQkLwI7+5uIRpLE++OtA7XIubpeVg/WuQJ4hkt7PZpWCfsjI3o4cva//SKA/S7Xz/ZnpuSzZRlNompMxdhk0vkvSoRuUvrPjurvL3ZdYzqhX5+/gcGbgE3wxns6S38+wx91PNfA43wHSGX1JaFxmyX6uJn02fGcNfsvpGGTow9BYXiV/gNXLV9U7cGPyecuidWzr2OepUdQKMd4l5u3ywXwbOrpJ+3+4QB/1ubD7OYhdPWPeF5IKOGOK5nH2Dj/MTLYpjDLDuHhU2XSgcbtteVdnerjPUBYtMRr7XsW+FAGJVCDwgVw3u5zY35JE9z0BJIU2nJ/8/84fwwvnzchrxobw26C6WMuQ84WPp/++Y5MEihCWTsaToyWqDjYvIyaMZcPet8K8Y4bGauzam+dHNi0KyrXKOnjeScXTUlCslj03daClmZYJCUoas9xl1KyTJc1ZKXceTJhmNMsTL1JGxhOWo4DWY7bx32o2SY8SokE7paJxfbfn5rMjK1fFD/Km+BexfksyGbFRXubtLyomZGs97eqVX+1cU1Qv0yRHrVZRQayPQxzjWuYjGLkGPFjpNhWjEOd8+eustnNAW7Sr4s84Pt2WOo5vk40ShqciU0mlYyrDMko/xBhpbKydexFvd3X1WOLHE/Ve57Va9f4sfJ5WOPqwdK/m20aObv1Xr3mrxnguXucH2ooXLaEf/zP4EdfvvRPmXVHrLr6+p/UWbb0mbSlg+eSHwyJaGiRzInziBP7VviLk0jySbJxP1FIDsZ0M5OjyDmVcRHz1GhnkwhSkaIXC8pzRbIluHvk+cQ+MyZF0IwGXlRwcV5ol3E+mHWb7dosWypmBpdOb37yxiDfEf5pUf4WH5uMjfCrXDIiXPrqB3587yUrmLPzQo9n3W0EAR9D/RBkwz7yuZqcWtra8lPEpz0XyP+wqFJHS9UvhtqiwaCcaCJKvKOQkIaUu5I/0658Z3C3Tjd0OstLwpK2otzf4NaR1sfftxG9Vm8RV1U5K5agplNuhYuDL4yeBlM1+vT4e3zS5h57Qxon8BkDoxziLaqqhOuDA//0zd31++dE0aYeKGjj/tn6f4/NJoTIMWYerVLnVT770z7tzewCU+TaoMzryLY7/JsWciAvCxRflvejOFFdeYuTeK2rH63p2MT0x0Fdfgz/ZBxdZ9K3bHzCvfyqlxKouT692muNgH+T23NTTy7X0ZuLx5X1UTZ1/P5XJ7IJandzc3YUURN7jgpBwryeVEv/UsE5Jq5BykEagaW3ExyemM1rf2nodx6n+5ycn4mMbq2zJOL8LfxCHO1l5gXy09NBiaZZkg0sBPIFYc8aOSm3x8jv5/cbY2/dPbr4vmx63xWPH30vfRThxa8QhHzoPhVv//bB6H3hhHLDBi1BOr+gFiTXW03/4n6glpPkwCy6JCeXUAvvklZyjYzWmSUnrKcOs5bJZe9vNDnrGni/MVylDGe/9Tpr/4AeTxvNWeDJtfeZSeX12b2W6W9MKlEk6W39V0H1KxP8O15JuxbtmprXx1/NPqTB306TKQn0sKNwcFxQuSup/vQvq8CUy5OkSiA8myfXLz6/jc+Ry2uxWINqa+SZ1fZubc4ErR4N+f7H0BVCF68SJ1iyfxKjcluEIycXI/c5f743Vox1ZPhRf5BWdjifRAhP7xmT7JWV9/RhxvOX8T+MLDOilqTZufDs/4e1KXXqcw+1dcq3abK0TuI35j3M3d4bLs5wo3tPmeBZcAmPWBKNv0bz4cg48J9VO8DF31iKqf4v7X4v7NJp/Ekc3OlG61tMV/4Msy8zlsXyt2v5uj9/dH9hGfhp8pnZQkoxl/uW9GW++N8X3MZnZzygD/oaRk91x+n54sZYg7NGDoVf82UFJJJaAKdM2/fxUSZaCOH89tBHiB3mfy+XYRpPejoiedNr2/j63rYHr1c77f9e2ReWTLw61YcPsgxPDGxQ4QUMQ8n+IADa8Kw2aDsHYKn7VvXdvV/3XgbN/G6f9N2aIq0e/n+uOaXf4EUPaiARM/jzJxClUfqeFlZtVmKt7c5t7VVG+8rcOncYKfvGTwAF/X/A+823fuxKDv0K6DckUFyQYRjkdd3dWMI/qlzxoo9eKNjJMj/U3D9g61Kl+JM9GDgM6td7ISd0sfmfVbv3kZBaSyTvqSTS/ugdcaVPz0eSVP+BRvsbAJo9g+ZM3vuaQxEaJua4L7cqV06HC8ls04fjL+0I+pwnkr0Q5vXOnHkf4tkpFBVZUlcJYrF71RIIfmNrckckuyehSpGPDzw//e87234H/y0+hfYknygW+nBDv+192UUhnPr3PhV76tHazf7zoeGVKjUfgpzD3LteMOuY+qYhSzDhZZQXRCTVcmcGzHhDviy8zXcxfP8Dwrd+/GE/l0BBgMOPy59bXa6dVrj/viMSNZlPdMykl2F0l23sM8y5tYt0aPFCL1M/OhHsUNxnugbhXkzprfw5+JqMYv4BoLN+/iscBo/Jm2eFLY0aiqs9/Py7qcvVz28kg1ySCfIWc2Nn+HwHkr5IuQYOSjoy00/uEnBRvZctooG8/l5zRQplq12Xs5YpOeTYDXwbro7kaKh/DRmmfha7n4mIX/3BThun5w9nN+8piXhyRdsukfkXTHa5L92jKHMZlJHuLra3xA5byMqI+x4qJaPb9rOYi6+JMa+H3VcuSnd3uFruT60YjYV4jOBVQXja0Xd1h1L/sv7IRr+JM/2Dd39JNIR252Cd5xo6vA1lofyY73WajdOYb6tjwlP8g3fZLaXfiCeYt0vrKzxp7L1ifMWld1ufv6f/IgVtiOEziPRb1uy1n/AMe/WzWTaLhVBtj2vscymQizO8xqeKShvCkL2SRape/UlsW6VCPEN/uW8/vD1lCO7o79Fnbv2sW+vHn2eG4dTRN5EH+6RL4yF/fiJRHPUWqX81me5s9BLHDzcxcDdXGjXf+at52zka9Gnk7Jkbs0fR5xEjbVLZy28ZSTTvI3ib1jCjgM3cWV24y2aSgcbyVlzcnA163gbTJosdl8H1tJemkEW/zUb2nv3ZhRYxP9snsuteaw/jvucb1aOGLOL3S/lFfN+K4YxJalefl35kgzhXYgRPBIR0fpf1v6yUFZ+Xg5vS/YQDnApiv8CDstjKYy53tM4=
*/