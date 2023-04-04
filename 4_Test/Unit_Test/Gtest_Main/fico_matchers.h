/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
*  @brief File to implement Ficosa internal matchers.
*  @author  F59CGR0
*******************************************************************************/

#ifndef FICO_MATCHERS_H
#define FICO_MATCHERS_H

template<typename T, size_t size>
::testing::AssertionResult ArraysMatch(const T (&expected)[size],
                                       const T (&actual)[size]){
    for (size_t i(0); i < size; ++i){
        if (expected[i] != actual[i]){
            return ::testing::AssertionFailure() << "array[" << i
                << "] (" << actual[i] << ") != expected[" << i
                << "] (" << expected[i] << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

ACTION_P2(FillInterComs, value, size)
{
	memcpy((void*)arg2, &value, size);
}

ACTION_P2(CopyBufferToArg0, value, size)
{
    memcpy((void*)arg0, value, size);
}

ACTION_TEMPLATE( StringCpyToArg, HAS_1_TEMPLATE_PARAMS(int, k), AND_2_VALUE_PARAMS(src, src_size)) {
    strncpy((char *)std::tr1::get<k>(args), src, src_size);
}
ACTION_TEMPLATE( MemCpyToArg, HAS_1_TEMPLATE_PARAMS(int, k), AND_2_VALUE_PARAMS(src, src_size)) {
    memcpy((char*)std::tr1::get<k>(args), src, src_size);
}

#endif // FICO_MATCHERS_H
