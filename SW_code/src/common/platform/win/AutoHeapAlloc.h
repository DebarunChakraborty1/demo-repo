/*
 * Copyright (c) 2016 Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 *   3. Neither the name of Nordic Semiconductor ASA nor the names of other
 *   contributors to this software may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 *   4. This software must only be used in or with a processor manufactured by Nordic
 *   Semiconductor ASA, or in or with a processor manufactured by a third party that
 *   is used in combination with a processor manufactured by Nordic Semiconductor.
 *
 *   5. Any software provided in binary or object form under this license must not be
 *   reverse engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
Module : AutoHeapAlloc.h
Purpose: Defines the interface for a class which supports auto closing of a heap pointer allocated via HeapAlloc
Created: PJN / 10-01-2013

Copyright (c) 2013 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


///////////////////////// Macros / Structs etc ////////////////////////////////

#pragma once

#ifndef __AUTOHEAPALLOC_H__
#define __AUTOHEAPALLOC_H__


///////////////////////// Includes ////////////////////////////////////////////                      

#include <assert.h>


///////////////////////// Classes /////////////////////////////////////////////

class CAutoHeapAlloc
{
public:
//Constructors / Destructors
  CAutoHeapAlloc(HANDLE hHeap = GetProcessHeap(), DWORD dwHeapFreeFlags = 0) : m_pData(NULL),
                                                                               m_hHeap(hHeap),
                                                                               m_dwHeapFreeFlags(dwHeapFreeFlags)
  {
  }

  BOOL Allocate(SIZE_T dwBytes, DWORD dwFlags = 0)
  {
    //Validate our parameters
    assert(m_pData == NULL);

    m_pData = HeapAlloc(m_hHeap, dwFlags, dwBytes);
    return (m_pData != NULL);
  }

  ~CAutoHeapAlloc()
  {
    if (m_pData != NULL)
    {
      HeapFree(m_hHeap, m_dwHeapFreeFlags, m_pData);
      m_pData = NULL;
    }
  }

//Methods

//Member variables
  LPVOID m_pData;
  HANDLE m_hHeap;
  DWORD  m_dwHeapFreeFlags;
};

#endif //__AUTOHEAPALLOC_H__
