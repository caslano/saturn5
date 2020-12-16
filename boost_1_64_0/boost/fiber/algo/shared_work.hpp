
//          Copyright Nat Goodspeed + Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_SHARED_WORK_H
#define BOOST_FIBERS_ALGO_SHARED_WORK_H

#include <condition_variable>
#include <chrono>
#include <deque>
#include <mutex>

#include <boost/config.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {
namespace algo {

class BOOST_FIBERS_DECL shared_work : public algorithm {
private:
    typedef std::deque< context * >  rqueue_type;
    typedef scheduler::ready_queue_type lqueue_type;

    static rqueue_type     	rqueue_;
    static std::mutex   	rqueue_mtx_;

    lqueue_type            	lqueue_{};
    std::mutex              mtx_{};
    std::condition_variable cnd_{};
    bool                    flag_{ false };
    bool                    suspend_{ false };

public:
    shared_work() = default;

    shared_work( bool suspend) :
        suspend_{ suspend } {
    }

	shared_work( shared_work const&) = delete;
	shared_work( shared_work &&) = delete;

	shared_work & operator=( shared_work const&) = delete;
	shared_work & operator=( shared_work &&) = delete;

    void awakened( context * ctx) noexcept override;

    context * pick_next() noexcept override;

    bool has_ready_fibers() const noexcept override {
        std::unique_lock< std::mutex > lock{ rqueue_mtx_ };
        return ! rqueue_.empty() || ! lqueue_.empty();
    }

	void suspend_until( std::chrono::steady_clock::time_point const& time_point) noexcept override;

	void notify() noexcept override;
};

}}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_SHARED_WORK_H

/* shared_work.hpp
uSG5r1vUPtta+1djYXmnehYNlHqVzphhq/TCRBRrveIyenuxvXgmFBe0CV+RB2KhMb3CVvLvCdqSRYZxq63kb9hrRqesAAuZ9p6FjbPtqCvrAYRNrPaZyMghqp8ebMMwBDBQ1nl59bveRGLvp/cje2+xsvdOEevjMR2EvQM4lTclhSCp1poUhqQ/QZKRM9NBLjtutrVwrdtOY8BEY46IecKaRms7M29wWzpRkOT4xNz6naicqDx4H1I5w0rlYxCcN26ZUb9XEM/sjT3salRjx8+1wb3ksjQ2RI09Oqd+YxdQY4eJxs60Nvbba+uPN3/9Vl/Yn8K/Kar66GBToTAVulVT91Kq+517se5Z1rrnQN0E2RdCv9T+XvIpbOTIp0LjFHii7t9GPgUN7yIxGfD/j08G/gd/Jv+idJplP32W8eINcfffBy3lF4p546wpapPYa3MwAX/ivTI4tmLbAeG5LMobq5IyNhnNVVrjZjz14r9TTVFWDi1UibojKdQ7J6L7iQOXXt9cxAsmcxfaYSB8drZIwAbXeEU52eCgaPDu5irtmMS/iJQssf4xhfhJMerk15KysUHRDApJ494oaHFSdmVSNtSWtaXx81XBqJ9L7GiOEBmOYFEWBzUaqTCySNBWFyZ6moS/V1PwZzUd/3ulTcCf2XT8U5uC30v44/fPYrFzsdR2fknsvC3raLzT37ywQ1sa+2P8PQWbUC6yyNHvBf2Vno70M5+Mk+HAWaTTey9nJ3ch6/QnR4GT+5i0v6XCjy/7SQHiEgnozVEOWm96COUY66AZ9aqZT9W8tQyrWWytZhBWMwBjfOkSS9BH7v72MmEnC0Uy7aEu4IpIg4CN6hNL8gyDpBWhzdsSEQGaMswYAlfWQ9mMK8mPqnwXJ91jCsGyP4HBCXuEdCW11bdMw5KVV0FbMUZJ+4moZo6DX3opoJMkeFXlxXQuDEwxOwX+Ap7DgjfQLkCNIAUjrLha7sHm/IKa87O7sDmJ1uakQHOiKWRt95+jBP1IX3zCbtAHugHoMbpDDJwO5i/mBCgnYNyONVJ0/+Xi76WH/lM/8/pvic3+9AP/oqK6+cqKz5snvrT5YKKwEI2J14cQ3eoS80lUXibKlBNHr5g40rh7GbJpG++rMAGlpzvPl+OTXufI1xx6nUKvvKKYEI0YbafylL6Q1tA/ukGuyFxpHJrCmUW01P4blXk+n1Hx8dEsv7F7uszuWGA5uRWG/nZhrtQD1Jiy82Uc8Ycv98bRl8jeGHcHTqI4xg3XUFNgrnqemuO3my55RaqNWB6QLM/B1QUMhiuTHU0RR7Sq1REt38wAJohjc1BfdsaGGnjP/sM2VMSdYe8NKIw2lSPVobWjQySfLo4+X2A+fIZXUYPh59GaA+nSNf6gh3CNOxKGi69Ww67mJsnIqETeC7Not9lsHps3/ZDz0g39aCj8baLgLu3YmFTtgqNqiYHWrspUt3GX3NzYCdbjdp3X2gXd4QuIIcDblAvE20fjG7l1RSNf02j86UTLaU4vKO9iV+RUfhdnhIQW5BBWXbg4mqVJN7o2tjX69hjC/hfL4YyX5tHPsjMtRA+0BKeOFdTBj8e/mgjBqhEu7mTO7IlF1NQol5T0YjE1KkclPZeV9DiIGNeWNIen9ufZN9JeDslE5e1zVRe57FwsRQ2llDyRAs2VJl2+hui1syy/lE5tEQl4CKkZeJfzRGvrqld2e+ndgxglq8R/i0VqN7q3sBxnf7tV4K6sp7F8KiKkJTHOAxhaIgtl0coZVbIMKjHB5yD8zVcS/Cob/CqCz0H4VRJ+pBXeh/AnyfrX2eDXEbwP4ddJ+DZWeD/CH76C4Nfb4NcTvJ/ugSD49z0=
*/