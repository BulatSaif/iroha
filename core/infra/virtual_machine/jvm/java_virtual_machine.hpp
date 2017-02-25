/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

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

#ifndef IROHA_JAVA_VIRTUAL_MACHINE_HPP_HPP
#define IROHA_JAVA_VIRTUAL_MACHINE_HPP_HPP

#include <jni.h>
#include <memory>
#include <string>

#include <iostream>
#include <map>

namespace virtual_machine {
namespace jvm {
    struct JavaContext {
        JNIEnv *env;
        JavaVM *jvm;
        jclass jClass;
        jobject jObject;
        std::string name;
        JavaVMInitArgs vmArgs;

        JavaContext(
                JNIEnv *aEnv,
                JavaVM *aJvm,
                JavaVMInitArgs aArgs,
                std::string aName,
                jclass cls,
                jobject obj
        ) :
                env(std::move(aEnv)),
                jvm(std::move(aJvm)),
                jClass(std::move(cls)),
                jObject(std::move(obj)),
                name(std::move(aName)),
                vmArgs(std::move(aArgs)) {}
    };


    void Java_SmartContract_save(JNIEnv *env, jobject thiz, jstring key, jstring value);
    std::unique_ptr<JavaContext> initializeVM(const std::string& packageNameUnderInstances, const std::string& contractName);

    // Tempolary implementation.
    // If variadic types of parameters are needed, consider to use JSON, I think.
    // I think it is hard for Java program to use HashMap only.
    void execFunction(
        const std::unique_ptr<JavaContext> &context,
        std::string functionName,
        std::map<std::string, std::string> params
    );

    void execFunction(
        const std::unique_ptr<JavaContext> &context,
        std::string functionName,
        std::map<std::string, std::string> params,
        std::map<std::string, std::map<std::string, std::string>> params2
    );

    void execFunction(
        const std::unique_ptr<JavaContext> &context,
        std::string functionName,
        std::map<std::string, std::string> params,
        std::vector<std::string> params2
    );

    void execFunction(
        const std::unique_ptr<JavaContext> &context,
        std::string functionName
    );

}
}

#endif //IROHA_JAVA_VIRTUAL_MACHINE_HPP_HPP
