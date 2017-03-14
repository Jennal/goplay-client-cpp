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

#ifndef HEADER_TEST_HPP
#define HEADER_TEST_HPP

#include "header.hpp"
#include "test_common.hpp"

void header_test() {
    Header header4((PackageType)128, (EncodingType)255, (PackageIDType)256, STAT_OK, (PackageSizeType)32768, "gate.getname");
    header_print(header4);

    Bytes b4;
    header4.GetBytes(b4);
    bytes_print(b4);
    header4.SetBytes(b4);
    header_print(header4);

    for(int i=0; i<512; ++i) {
        Header header3((PackageType)1, (EncodingType)2, (PackageIDType)3, "connector.hello");
        header_print(header3);
        Bytes b3;
        header3.GetBytes(b3);
        bytes_print(b3);
    }

    Header header((PackageType)1, (EncodingType)2, (PackageIDType)3, "");
    header_print(header);
    Bytes b3;
    header.GetBytes(b3);
    bytes_print(b3);
    header.SetBytes(b3);
    header_print(header);
}

#endif