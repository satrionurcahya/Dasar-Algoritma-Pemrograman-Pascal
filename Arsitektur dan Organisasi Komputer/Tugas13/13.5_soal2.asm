# =====================================================
# TUGAS 13.5 - SOAL 2
# hasil = (a × b) + c, dengan a=7, b=6, c=10
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanHasil : .asciiz "Hasil (a*b)+c = "

.text
.globl main

main:
    li $t0, 7           # a = 7
    li $t1, 6           # b = 6
    li $t2, 10          # c = 10

    # Hitung a * b
    mult $t0, $t1
    mflo $t3            # $t3 = 7 * 6 = 42

    # Tambahkan c
    add  $s0, $t3, $t2  # $s0 = 42 + 10 = 52

    # Tampilkan
    li $v0, 4
    la $a0, pesanHasil
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall