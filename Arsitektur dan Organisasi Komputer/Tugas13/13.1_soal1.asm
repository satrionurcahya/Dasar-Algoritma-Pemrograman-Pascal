# =====================================================
# TUGAS 13.1 - SOAL 1
# a = b + c
# d = a - e
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanA : .asciiz "Nilai a = "
    pesanD : .asciiz "\nNilai d = "

.text
.globl main

main:
    # Inisialisasi nilai awal
    li $t0, 20          # b = 20
    li $t1, 10          # c = 10
    li $t2, 5           # e = 5

    # Hitung a = b + c
    add $s0, $t0, $t1   # $s0 (a) = 20 + 10 = 30

    # Hitung d = a - e
    sub $s1, $s0, $t2   # $s1 (d) = 30 - 5 = 25

    # Tampilkan hasil a
    li $v0, 4
    la $a0, pesanA
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    # Tampilkan hasil d
    li $v0, 4
    la $a0, pesanD
    syscall

    li $v0, 1
    move $a0, $s1
    syscall

    # Keluar
    li $v0, 10
    syscall