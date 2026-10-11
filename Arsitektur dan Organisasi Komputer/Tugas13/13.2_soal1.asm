# =====================================================
# TUGAS 13.2 - SOAL 1
# g = h + A[3]
# Array A = {10, 20, 30, 40, 50}, h = 5
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    A      : .word 10, 20, 30, 40, 50
    h      : .word 5
    pesanG : .asciiz "Nilai g = "

.text
.globl main

main:
    # Load h = 5
    lw $t0, h           # $t0 = 5

    # Load A[3] -> alamat A + (3 * 4 byte)
    la $t1, A           # $t1 = alamat dasar array A
    lw $t2, 12($t1)     # $t2 = A[3] = 40  (offset 3 * 4 = 12)

    # Hitung g = h + A[3]
    add $s0, $t0, $t2   # $s0 (g) = 5 + 40 = 45

    # Tampilkan hasil
    li $v0, 4
    la $a0, pesanG
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall