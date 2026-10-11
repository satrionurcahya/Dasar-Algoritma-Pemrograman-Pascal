# =====================================================
# TUGAS 13.5 - SOAL 4
# hasil = (a × b) − (c × d)
# a=9, b=5, c=4, d=3
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanHasil : .asciiz "Hasil (a*b)-(c*d) = "

.text
.globl main

main:
    li $t0, 9           # a = 9
    li $t1, 5           # b = 5
    li $t2, 4           # c = 4
    li $t3, 3           # d = 3

    # Hitung a * b
    mult $t0, $t1
    mflo $t4            # $t4 = 45

    # Hitung c * d
    mult $t2, $t3
    mflo $t5            # $t5 = 12

    # Hitung hasil = (a*b) - (c*d)
    sub  $s0, $t4, $t5  # $s0 = 45 - 12 = 33

    # Tampilkan
    li $v0, 4
    la $a0, pesanHasil
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall