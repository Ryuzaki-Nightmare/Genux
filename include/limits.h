#ifndef LIMITS_H
#define LIMITS_H

#define __STDC_VERSION_LIMITS_H__ 202311L

/* Usar as constantes nativas do compilador evita erros de arquitetura */

/* Largura máxima para inteiros de tamanho preciso (_BitInt) */
#ifdef __BITINT_MAXWIDTH__
  #define BITINT_MAXWIDTH  __BITINT_MAXWIDTH__
#else
  #define BITINT_MAXWIDTH  1024
#endif

/* Tipo _Bool / bool */
#define BOOL_MAX         1
#define BOOL_WIDTH       8

/* Número de bits em um byte */
#define CHAR_BIT         __CHAR_BIT__

/* Largura dos tipos básicos */
#define CHAR_WIDTH       __CHAR_BIT__
#define SCHAR_WIDTH      __CHAR_BIT__
#define UCHAR_WIDTH      __CHAR_BIT__
#define SHRT_WIDTH       __SHRT_WIDTH__
#define USHRT_WIDTH      __SHRT_WIDTH__
#define INT_WIDTH        __INT_WIDTH__
#define UINT_WIDTH       __INT_WIDTH__
#define LONG_WIDTH       __LONG_WIDTH__
#define ULONG_WIDTH      __LONG_WIDTH__
#define LLONG_WIDTH      __LONG_LONG_WIDTH__
#define ULLONG_WIDTH     __LONG_LONG_WIDTH__

/* Limites de Caractere (Assinado vs Não-Assinado) */
#ifdef __CHAR_UNSIGNED__
  #define CHAR_MIN       0
  #define CHAR_MAX       __UCHAR_MAX__
#else
  #define CHAR_MIN       (-__SCHAR_MAX__ - 1)
  #define CHAR_MAX       __SCHAR_MAX__
#endif

/* Limites de Tipos Inteiros Assinados */
#define SCHAR_MIN        (-__SCHAR_MAX__ - 1)
#define SCHAR_MAX        __SCHAR_MAX__

#define SHRT_MIN         (-__SHRT_MAX__ - 1)
#define SHRT_MAX         __SHRT_MAX__

#define INT_MIN          (-__INT_MAX__ - 1)
#define INT_MAX          __INT_MAX__

#define LONG_MIN         (-__LONG_MAX__ - 1L)
#define LONG_MAX         __LONG_MAX__

#define LLONG_MIN        (-__LONG_LONG_MAX__ - 1LL)
#define LLONG_MAX        __LONG_LONG_MAX__

/* Limites de Tipos Inteiros Não-Assinados */
#define UCHAR_MAX        __UCHAR_MAX__
#define USHRT_MAX        __USHRT_MAX__
#define UINT_MAX         __UINT_MAX__
#define ULONG_MAX        __ULONG_MAX__
#define ULLONG_MAX       __LONG_LONG_MAX__ * 2ULL + 1ULL

/* Número máximo de bytes em um caractere multibyte (Padrão seguro para OS) */
#define MB_LEN_MAX       4



#endif