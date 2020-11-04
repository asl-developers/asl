#ifndef _INTPSEUDO_H
#define _INTPSEUDO_H
/* intpseudo.h */
/*****************************************************************************/
/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only                     */
/*                                                                           */
/* AS-Portierung                                                             */
/*                                                                           */
/* Commonly used 'Intel Style' Pseudo Instructions                           */
/*                                                                           */
/*****************************************************************************/
  
/*****************************************************************************
 * Global Functions
 *****************************************************************************/

extern void DecodeIntelDN(Word BigEndian);
extern void DecodeIntelDB(Word BigEndian);
extern void DecodeIntelDW(Word BigEndian);
extern void DecodeIntelDD(Word BigEndian);
extern void DecodeIntelDQ(Word BigEndian);
extern void DecodeIntelDT(Word BigEndian);
   
extern Boolean DecodeIntelPseudo(Boolean BigEndian);

#endif /* _INTPSEUDO_H */
