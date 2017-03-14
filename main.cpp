// Copyright (C) 2017 Jennal(jennalcn@gmail.com). All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include <iostream>
#include "bytes_test.hpp"
#include "header_test.hpp"
#include "tcpclient_test.hpp"
#include "thread_test.hpp"
#include "client_test.hpp"
#include "client_test.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // bytes_test();
    // header_test();
    // tcpclient_test();
    // thread_test();
    client_test();

    return 0;
}
