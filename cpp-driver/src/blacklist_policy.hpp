/*
  Copyright (c) 2014-2017 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef __CASS_BLACKLIST_POLICY_HPP_INCLUDED__
#define __CASS_BLACKLIST_POLICY_HPP_INCLUDED__

#include "load_balancing.hpp"
#include "host.hpp"
#include "scoped_ptr.hpp"
#include "list_policy.hpp"

namespace cass {

class BlacklistPolicy : public ListPolicy {
public:
  BlacklistPolicy(LoadBalancingPolicy* child_policy,
                  const ContactPointList& hosts)
    : ListPolicy(child_policy)
    , hosts_ (hosts) {}

  virtual ~BlacklistPolicy() {}

  BlacklistPolicy* new_instance() {
    return Memory::allocate<BlacklistPolicy>(child_policy_->new_instance(), hosts_);
  }

private:
  bool is_valid_host(const Host::Ptr& host) const;

  ContactPointList hosts_;

private:
  DISALLOW_COPY_AND_ASSIGN(BlacklistPolicy);
};

} // namespace cass

#endif
