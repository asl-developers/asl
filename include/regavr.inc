                save
                listing off   ; kein Listing ueber diesen File

;****************************************************************************
;*                                                                          *
;*   AS 1.41 - Datei REGAVR.INC                                             *
;*                                                                          *
;*   Sinn : enth�lt SFR- und Bitdefinitionen fuer die AVR-Prozessoren       *
;*                                                                          *
;*   letzte �nderungen :  6. 7.1996                                         *
;*                        8. 6.1997 Anpassung an die endgueltigen Versionen *
;*                       19.11.1999 Konstantenmodus fuer AVR jetzt HEX      *
;*                       26. 2.2000 MomCPU-->MOMCPU fuer case-sensitiven    *
;*                                  Modus                                   *
;*                                                                          *
;****************************************************************************

                ifndef  regavrinc       ; verhindert Mehrfacheinbindung

regavrinc       equ     1

                if      (MOMCPUNAME<>"AT90S1200")&&(MOMCPUNAME<>"AT90S2313")&&(MOMCPUNAME<>"AT90S4414")&&(MOMCPUNAME<>"AT90S8515")
                 fatal  "Falscher Prozessortyp eingestellt: nur AT90S1200, AT90S2313, AT90S4414 oder AT90S8515 erlaubt!"
                endif


                if      MOMPASS=1
                 message "Atmel-AVR-SFR-Definitionen (C) 1996 Alfred Arnold"
                endif

;----------------------------------------------------------------------------
; Prozessorkern

sreg            port    0x3f            ; Statusregister:
c               equ     0               ;  Carry
z               equ     1               ;  Ergebnis Null
n               equ     2               ;  Ergebnis negativ
v               equ     3               ;  Zweierkomplement-�berlauf
s               equ     4               ;  Vorzeichen
h               equ     5               ;  Halfcarry
t               equ     6               ;  Bitspeicher
i               equ     7               ;  globale Interruptsperre

                if      MOMCPU>=0x902313
spl              equ     0x3d           ; Stapelzeiger (MSB)
                 if      MOMCPU>=0x904414
sph               equ     0x3e          ;              (LSB)
                 endif
                endif

;----------------------------------------------------------------------------
; Chip-Konfiguration

mcucr           port    0x35            ; CPU-Steuerung:
isc00           equ     0               ;  Flankenwahl INT0
isc01           equ     1               ;  Flanken/Pegeltriggerung INT0
                if      MOMCPU>=0x902313
isc10            equ     2              ;  Flankenwahl INT1
isc11            equ     3              ;  Flanken/Pegeltriggerung INT1
                endif
sm              equ     4               ;  Idle/Powerdown-Modus w�hlen
se              equ     5               ;  Sleep-Modus freigeben
                if      MOMCPU>=0x904414
srw              equ     6              ;  Wait-State-Wahl externes SRAM
sre              equ     7              ;  Freigabe externes SRAM
                endif

;----------------------------------------------------------------------------
; Interrupt-Steuerung

gimsk           port    0x3b            ; generelle Interrupt-Maske:
int0            equ     6               ;  externer Interrupt 0
                if      MOMCPU>=0x902313
int1             equ     7              ;  externer Interrupt 1
                endif

                if      MOMCPU>=0x902313
gifr		 port	 0x3a           ; generelle Interrupt-Flags:
intf0		 equ	 6		;  externer Interrupt 0
intf1            equ     7              ;  externer Interrupt 1
                endif

timsk           port    0x39            ; Timer-Interrupt-Maske:
toie0           equ     1               ;  �berlauf Timer 0
                if      MOMCPU>=0x902313
                 if      MOMCPU>=0x904414
ocie1b            equ     5             ;  Vergleich B Timer 1
                 endif
ocie1a           equ     6              ;  Vergleich Timer 1
toie1            equ     7              ;  �berlauf Timer 1
ticie1           equ     3              ;  Fang Timer 1
                endif

tifr            port    0x38            ; Timer-Interrupt-Flags:
tov0            equ     1               ;  �berlauf Timer 0
                if      MOMCPU>=0x902313
                 if      MOMCPU>=0x904414
ocf1b             equ     5             ;  Vergleich B Timer 1
                 endif
ocf1a            equ     6              ;  Vergleich A Timer 1
tov1             equ     7              ;  �berlauf Timer 1
icf1             equ     3              ;  Fang Timer 1
                endif

;----------------------------------------------------------------------------
; parallele Ports

                if      MOMCPU>=0x904414
porta            port    0x1b           ; Datenregister Port A
ddra             port    0x1a           ; Datenrichtungsregister Port A
pina             port    0x19           ; Leseregister Port A
                endif

portb           port    0x18            ; Datenregister Port B
ddrb            port    0x17            ; Datenrichtungsregister Port B
pinb            port    0x16            ; Leseregister Port B

                if      MOMCPU>=0x904414
portc            port    0x15           ; Datenregister Port C
ddrc             port    0x14           ; Datenrichtungsregister Port C
pinc             port    0x13           ; Leseregister Port C
                endif

portd           port    0x12            ; Datenregister Port D
ddrd            port    0x11            ; Datenrichtungsregister Port D
pind            port    0x10            ; Leseregister Port D

;----------------------------------------------------------------------------
; Timer

tccr0           port    0x33            ; Steuerregister Timer 0:
cs00            equ     0               ;  Vorteilereinstellung
cs01            equ     1
cs02            equ     2

tcnt0           port    0x32            ; Z�hlregister Timer 0

                if      MOMCPU>=0x902313
tccr1a           port    0x2f           ; Steuerregister A Timer 1:
pwm10            equ     0              ;  Modus Pulsweitenmodulator
pwm11            equ     1
com1a0           equ     6              ;  Vergleichsmodus A
com1a1           equ     7
                 if      MOMCPU>=0x904414
com1b0            equ     4             ;  Vergleichsmodus B
com1b1            equ     5
                 endif

tccr1b           port    0x2e           ; Steuerregister B Timer 1:
cs10             equ     0              ; Vorteilereinstellung
cs11             equ     1
cs12             equ     2
ctc1             equ     3              ; nach Gleichheit zur�cksetzen ?
ices1            equ     6              ; Flankenwahl Fang
icnc1            equ     7              ; Rauschfilter f�r Fangfunktion

tcnt1l           port    0x2c           ; Z�hlregister Timer 1 (LSB)
tcnt1h           port    0x2d           ;                      (MSB)

                 if      MOMCPU>=0x904414
ocr1al            port    0x2a          ; Vergleichsregister A Timer 1 (LSB)
ocr1ah            port    0x2b          ;                              (MSB)
ocr1bl            port    0x28          ; Vergleichsregister B Timer 1 (LSB)
ocr1bh            port    0x29          ;                              (MSB)
                 elseif
ocr1l             port    0x2a          ; Vergleichsregister Timer 1 (LSB)
ocr1h             port    0x2b          ;                            (MSB)
                 endif

icr1l            port    0x24           ; Fangwert Timer 1 (LSB)
icr1h            port    0x25           ;                  (MSB)
                endif

;----------------------------------------------------------------------------
; Watchdog

wdtcr           port    0x21            ; Watchdog-Steuerregister:
wdp0            equ     0               ;  Vorteiler
wdp1            equ     1
wdp2            equ     2
wde             equ     3               ; Freigabe
                if 	MOMCPU>=0x902313
wdttoe		 equ	 4		; zur Sperre gebraucht
                endif

;----------------------------------------------------------------------------
; serielle Ports

                if      MOMCPU>=0x902312
udr              port    0x0c           ; Datenregister UART

usr              port    0x0b           ; Statusregister UART:
or               equ     3              ;  Empf�nger�berlauf
fe               equ     4              ;  Framing-Fehler
udre             equ     5              ;  Datenregister wieder frei
txc              equ     6              ;  Sendung komplett
rxc              equ     7              ;  Empfang komplett

ucr              port    0x0a           ; Steuerregister UART:
txb8             equ     0              ;  Sendebit 8
rxb8             equ     1              ;  Empfangsbit 8
chr9             equ     2              ;  auf 9-Bit-Datenwerte umschalten
txen             equ     3              ;  Sender freigeben
rxen             equ     4              ;  Empf�nger freigeben
udrie            equ     5              ;  Interrupts bei freiem Datenregister freigeben
txcie            equ     6              ;  Interrupts nach Versand freigeben
rxcie            equ     7              ;  Interrupts nach Empfang freigeben

ubrr             port    0x09           ; Baudratengenerator
                endif

                if      MOMCPU>=0x904414
spcr             port    0x0d           ; SPI Steuerregister:
spr0             equ     0              ;  Wahl Taktfrequenz
spr1             equ     1
cpha             equ     2              ;  Taktphase
cpol             equ     3              ;  Taktpolarit�t
mstr             equ     4              ;  Master/Slave-Wahl
dord             equ     5              ;  Bitreihenfolge
spe              equ     6              ;  SPI freigeben
spie             equ     7              ;  Interruptfreigabe SPI

spsr             port    0x0e           ; SPI Statusregister:
wcol             equ     6              ;  Schreibkollision ?
spif             equ     7              ;  SPI-Interrupt aufgetreten ?

spdr             port    0x0f           ; SPI Datenregister
                endif

;----------------------------------------------------------------------------
; Analogkomparator

acsr            port    0x08            ; Komparator-Steuer/Statusregister:
acis0           equ     0               ;  Interrupt-Modus
acis1           equ     1
		if	MOMCPU>=0x902313
acic             equ     2              ;  Komparator als Fangsignal f�r Timer 1 benutzen
		endif
acie            equ     3               ;  Interrupt freigeben
aci             equ     4               ;  Interrupt aufgetreten ?
aco             equ     5               ;  Komparatorausgang
acd		equ	7		;  Strom abschalten

;----------------------------------------------------------------------------
; EEPROM

		if MOMCPU>=0x908515
eearl		 port	 0x1e		; Adre�register
eearh		 port	 0x1f
		elseif 
eear             port    0x1e
		endif

eedr            port    0x1d            ; Datenregister

eecr            port    0x1c            ; Steuerregister:
eere            equ     0               ;  Lesefreigabe
eewe            equ     1               ;  Schreibfreigabe
		if	MOMCPU>=0x902313
eemwe		 equ	 2
		endif

;----------------------------------------------------------------------------
; Vektoren
; Leider verschieben sich Vektoren bei den h�heren Prozessoren.
; Warum nur, Atmel, warum ?

vec_reset       label   0               ; Reset-Einsprung
vec_int0        label   1               ; Einsprung ext. Interrupt 0
                switch  MOMCPUNAME
                case    "AT90S1200"
vec_tm0ovf       label   2              ; Einsprung �berlauf Timer 0
vec_anacomp      label   3              ; Einsprung Analog-Komparator
                case    "AT90S2313"
vec_int1         label   2              ; Einsprung ext. Interrupt 2
vec_tm1capt      label   3              ; Einsprung Fang Timer 1
vec_tm1comp      label   4              ; Einsprung Vergleich Timer 1
vec_tm1ovf       label   5              ; Einsprung �berlauf Timer 1
vec_tm0ovf       label   6              ; Einsprung �berlauf Timer 0
vec_uartrx       label   7              ; Einsprung UART Empfang komplett
vec_uartudre     label   8              ; Einsprung UART Datenregister leer
vec_uarttx       label   9              ; Einsprung UART Sendung komplett
vec_anacomp      label   10             ; Einsprung Analog-Komparator
                case    "AT90S4414","AT90S8515"
vec_int1         label   2              ; Einsprung ext. Interrupt 2
vec_tm1capt      label   3              ; Einsprung Fang Timer 1
vec_tm1compa     label   4              ; Einsprung Vergleich A Timer 1
vec_tm1compb     label   5              ; Einsprung Vergleich A Timer 1
vec_tm1ovf       label   6              ; Einsprung �berlauf Timer 1
vec_tm0ovf       label   7              ; Einsprung �berlauf Timer 0
vec_spi          label   8              ; Einsprung SPI-Interrupt
vec_uartrx       label   9              ; Einsprung UART Empfang komplett
vec_uartudre     label   10             ; Einsprung UART Datenregister leer
vec_uarttx       label   11             ; Einsprung UART Sendung komplett
vec_anacomp      label   12             ; Einsprung Analog-Komparator
                endcase

;----------------------------------------------------------------------------
; Speicheradressen

eestart         equ     0               ; Startadresse internes EEPROM
iram            equ     96,data         ; Startadresse internes SRAM
                                        ; (hinter gemapptem I/O)
irom            label   0               ; Startadresse internes EPROM

                switch  MOMCPUNAME
                case    "AT90S1200"
eeend            equ     63             ; Endadresse EEPROM
iramend          equ     95,data        ; Endadresse SRAM
iromend          label   1023           ; Endadresse EPROM
                case    "AT90S2313"
eeend            equ     127
iramend          equ     0xdf,data
iromend          label   2047
                case    "AT90S4414"
eeend            equ     255
iramend          equ     0x15f,data
iromend          label   4095
                case    "AT90S8515"
eeend            equ     511
iramend          equ     0x25f,data
iromend          label   8191
                endcase

;----------------------------------------------------------------------------

                endif

                restore                 ; wieder erlauben


