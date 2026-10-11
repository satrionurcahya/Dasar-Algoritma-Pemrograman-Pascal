# =====================================================
# TUGAS 13.1 - SOAL 2
# f = (g + h) - (i + j)
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanF : .asciiz "Nilai f = "

.text
.globl main

main:
    # Inisialisasi nilai
    li $t0, 15          # g = 15
    li $t1, 8           # h = 8
    li $t2, 6           # i = 6
    li $t3, 3           # j = 3

    # Hitung (g + h) ke register sementara
    add $t4, $t0, $t1   # $t4 = 15 + 8 = 23

    # Hitung (i + j) ke register sementara
    add $t5, $t2, $t3   # $t5 = 6 + 3 = 9

    # Hitung f = (g+h) - (i+j)
    sub $s0, $t4, $t5   # $s0 (f) = 23 - 9 = 14

    # Tampilkan hasil
    li $v0, 4
    la $a0, pesanF
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall