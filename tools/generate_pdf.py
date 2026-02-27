"""
TEDAC HID — Button Assignment PDF Generator
Generates a professional, color-coded PDF from button assignment data.
"""

from reportlab.lib.pagesizes import A4
from reportlab.lib import colors
from reportlab.lib.units import mm
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.platypus import (
    SimpleDocTemplate, Table, TableStyle, Paragraph,
    Spacer, HRFlowable, KeepTogether
)
from reportlab.lib.enums import TA_CENTER, TA_LEFT
from reportlab.platypus import PageBreak
import os

# ── Output path ────────────────────────────────────────────────────────────────
OUTPUT = os.path.join(os.path.dirname(os.path.dirname(__file__)),
                      "TEDAC_Button_Assignment.pdf")

# ── Brand palette ──────────────────────────────────────────────────────────────
C_BG_PAGE   = colors.HexColor("#F5F7FA")   # document background (not directly set)
C_TITLE     = colors.HexColor("#1A2B4A")   # deep navy
C_SUBTITLE  = colors.HexColor("#2C5F8A")   # steel blue
C_RULE      = colors.HexColor("#3D7EC3")   # accent blue

# Section accent colours
C_TDU_HDR   = colors.HexColor("#1E3A5F")   # dark navy
C_TDU_SUB   = colors.HexColor("#2C5F8A")   # steel blue
C_TDU_ROW1  = colors.HexColor("#EBF3FB")   # very light blue
C_TDU_ROW2  = colors.white

C_LHG_HDR   = colors.HexColor("#1B4332")   # dark green
C_LHG_SUB   = colors.HexColor("#2D6A4F")   # forest green
C_LHG_ROW1  = colors.HexColor("#EAFAF1")   # very light green
C_LHG_ROW2  = colors.white
C_LHG_NEW   = colors.HexColor("#D4EDDA")   # highlighted mint — new trigger rows

C_RHG_HDR   = colors.HexColor("#6B2D0C")   # dark amber
C_RHG_SUB   = colors.HexColor("#C05621")   # burnt orange
C_RHG_ROW1  = colors.HexColor("#FEF3E2")   # very light amber
C_RHG_ROW2  = colors.white

C_AXS_HDR   = colors.HexColor("#44337A")   # deep purple
C_AXS_ROW1  = colors.HexColor("#F3EFFE")
C_AXS_ROW2  = colors.white

C_COL_HDR   = colors.HexColor("#F0F4FF")   # column header fill
C_TXT_DARK  = colors.HexColor("#1A1A2E")
C_TXT_MID   = colors.HexColor("#3B4863")
C_TXT_LIGHT = colors.HexColor("#FAFAFA")

# ── Typography ─────────────────────────────────────────────────────────────────
styles = getSampleStyleSheet()

def make_style(name, **kwargs):
    return ParagraphStyle(name, **kwargs)

S_TITLE = make_style("S_TITLE",
    fontSize=26, leading=32, textColor=C_TITLE,
    fontName="Helvetica-Bold", alignment=TA_CENTER, spaceAfter=4)

S_SUBTITLE = make_style("S_SUBTITLE",
    fontSize=13, leading=17, textColor=C_SUBTITLE,
    fontName="Helvetica", alignment=TA_CENTER, spaceAfter=2)

S_META = make_style("S_META",
    fontSize=9, leading=13, textColor=C_TXT_MID,
    fontName="Helvetica", alignment=TA_CENTER, spaceAfter=12)

S_SECTION = make_style("S_SECTION",
    fontSize=14, leading=18, textColor=C_TXT_LIGHT,
    fontName="Helvetica-Bold", alignment=TA_LEFT, spaceAfter=0, spaceBefore=14)

S_NOTE = make_style("S_NOTE",
    fontSize=8, leading=11, textColor=C_TXT_MID,
    fontName="Helvetica-Oblique", alignment=TA_LEFT, spaceAfter=8)

S_SUMMARY_HDR = make_style("S_SUMMARY_HDR",
    fontSize=11, leading=14, textColor=C_TXT_LIGHT,
    fontName="Helvetica-Bold", alignment=TA_LEFT)

# ── Helper: section header pill ────────────────────────────────────────────────
def section_header(title, subtitle, bg_color):
    data = [[Paragraph(f"<b>{title}</b>", S_SECTION),
             Paragraph(subtitle, S_NOTE)]]
    t = Table(data, colWidths=[100*mm, 90*mm])
    t.setStyle(TableStyle([
        ("BACKGROUND", (0,0), (-1,-1), bg_color),
        ("TOPPADDING",    (0,0), (-1,-1), 6),
        ("BOTTOMPADDING", (0,0), (-1,-1), 6),
        ("LEFTPADDING",   (0,0), (-1,-1), 8),
        ("RIGHTPADDING",  (0,0), (-1,-1), 8),
        ("ROWBACKGROUNDS", (0,0), (-1,-1), [bg_color]),
        ("VALIGN", (0,0), (-1,-1), "MIDDLE"),
    ]))
    return t

# ── Helper: generic button table ───────────────────────────────────────────────
def btn_table(col_headers, rows, hdr_color, row1, row2, highlight_rows=None):
    """
    col_headers : list[str]
    rows        : list[tuple]
    highlight_rows : set of row indexes (0-based in data, not counting header) to tint
    """
    highlight_rows = highlight_rows or set()
    col_w = [18*mm, 52*mm, 20*mm, 22*mm, 18*mm]

    # Build header row with Paragraphs
    hdr_style = ParagraphStyle("th",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    hdr = [Paragraph(h, hdr_style) for h in col_headers]

    cell_style = ParagraphStyle("td",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    cell_style_l = ParagraphStyle("tdl",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_LEFT, leading=11)

    data = [hdr]
    for r in rows:
        data.append([
            Paragraph(str(r[0]), cell_style),
            Paragraph(str(r[1]), cell_style_l),
            Paragraph(str(r[2]), cell_style),
            Paragraph(str(r[3]), cell_style),
            Paragraph(str(r[4]), cell_style),
        ])

    # Alternating colours
    row_fills = []
    for i in range(len(rows)):
        if i in highlight_rows:
            row_fills.append(C_LHG_NEW)
        elif i % 2 == 0:
            row_fills.append(row1)
        else:
            row_fills.append(row2)

    t = Table(data, colWidths=col_w, repeatRows=1)

    ts = TableStyle([
        # Header
        ("BACKGROUND",   (0,0), (-1,0), C_COL_HDR),
        ("LINEBELOW",    (0,0), (-1,0), 1.2, hdr_color),
        ("TOPPADDING",   (0,0), (-1,-1), 4),
        ("BOTTOMPADDING",(0,0), (-1,-1), 4),
        ("LEFTPADDING",  (0,0), (-1,-1), 5),
        ("RIGHTPADDING", (0,0), (-1,-1), 5),
        ("GRID",         (0,0), (-1,-1), 0.4, colors.HexColor("#D0D8E4")),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [row1, row2]),
        ("VALIGN",       (0,0), (-1,-1), "MIDDLE"),
    ])

    # Apply highlighted rows manually
    for i, fill in enumerate(row_fills):
        if i in highlight_rows:
            ts.add("BACKGROUND", (0, i+1), (-1, i+1), C_LHG_NEW)
            ts.add("FONTNAME",   (0, i+1), (-1, i+1), "Helvetica-Bold")

    t.setStyle(ts)
    return t

# ── Data ───────────────────────────────────────────────────────────────────────

HDR = ["HID #", "Name / Function", "STM32 Pin", "Port", "Pin #"]

AXES = [
    ("1", "Joystick X",   "PA6", "GPIOA", "CH3 / 6"),
    ("2", "Joystick Y",   "PA7", "GPIOA", "CH7 / 7"),
    ("3", "Joystick Z",   "PA2", "GPIOA", "CH14 / 2"),
    ("4", "Rotation X",   "PA3", "GPIOA", "CH15 / 3"),
    ("5", "Rotation Y",   "PC0", "GPIOC", "CH10 / 0"),
    ("6", "Rotation Z",   "PC1", "GPIOC", "CH11 / 1"),
]
AXES_HDR = ["Axis #", "Function", "STM32 Pin", "Port", "ADC Ch / Pin"]

TDU = [
    ("01","TDU TAD",       "PE0", "GPIOE","0"),
    ("02","TDU FCR",       "PE1", "GPIOE","1"),
    ("03","TDU PNV",       "PE2", "GPIOE","2"),
    ("04","TDU GS",        "PE3", "GPIOE","3"),
    ("05","TDU AZ",        "PE4", "GPIOE","4"),
    ("06","TDU SW6",       "PE5", "GPIOE","5"),
    ("07","TDU SW7",       "PE6", "GPIOE","6"),
    ("08","TDU LMC",       "PE7", "GPIOE","7"),
    ("09","TDU CAGE",      "PE8", "GPIOE","8"),
    ("10","TDU RF UP",     "PE9", "GPIOE","9"),
    ("11","TDU RF DOWN",   "PE10","GPIOE","10"),
    ("12","TDU EL UP",     "PE11","GPIOE","11"),
    ("13","TDU EL DOWN",   "PE12","GPIOE","12"),
    ("14","TDU SYM UP",    "PE13","GPIOE","13"),
    ("15","TDU SYM DOWN",  "PE14","GPIOE","14"),
    ("16","TDU BRT UP",    "PE15","GPIOE","15"),
    ("17","TDU BRT DOWN",  "PD8", "GPIOD","8"),
    ("18","TDU COM UP",    "PD9", "GPIOD","9"),
    ("19","TDU COM DOWN",  "PD10","GPIOD","10"),
    ("20","TDU DAY",       "PD11","GPIOD","11"),
    ("21","TDU NT",        "PD12","GPIOD","12"),
]

LHG = [
    ("22","LHG SW1",         "PD0", "GPIOD","0"),
    ("23","LHG SW2",         "PD1", "GPIOD","1"),
    ("24","LHG SW3",         "PD2", "GPIOD","2"),
    ("25","LHG SW4",         "PD3", "GPIOD","3"),
    ("26","LHG SW5",         "PD4", "GPIOD","4"),
    ("27","LHG HAT1 UP",     "PD5", "GPIOD","5"),
    ("28","LHG HAT1 DOWN",   "PD6", "GPIOD","6"),
    ("29","LHG HAT1 LEFT",   "PD7", "GPIOD","7"),
    ("30","LHG HAT1 RIGHT",  "PB0", "GPIOB","0"),
    ("31","LHG HAT2 UP",     "PB1", "GPIOB","1"),
    ("32","LHG HAT2 DOWN",   "PB2", "GPIOB","2"),
    ("33","LHG HAT2 LEFT",   "PB3", "GPIOB","3"),
    ("34","LHG HAT2 RIGHT",  "PB4", "GPIOB","4"),
    ("35","LHG HAT3 UP",     "PB5", "GPIOB","5"),
    ("36","LHG HAT3 DOWN",   "PB6", "GPIOB","6"),
    ("37","LHG HAT3 LEFT",   "PB7", "GPIOB","7"),
    ("38","LHG HAT3 RIGHT",  "PB8", "GPIOB","8"),
    ("39","LHG TEMP1 A",     "PB9", "GPIOB","9"),
    ("40","LHG TEMP1 B",     "PB10","GPIOB","10"),
    ("41","LHG TEMP2 A",     "PB11","GPIOB","11"),
    ("42","LHG TEMP2 B",     "PB12","GPIOB","12"),
    ("43","LHG TEMP3 A",     "PB13","GPIOB","13"),
    ("44","LHG TEMP3 B",     "PC4", "GPIOC","4"),
    ("45","LHG 3POS A",      "PC5", "GPIOC","5"),
    ("46","LHG 3POS B",      "PC6", "GPIOC","6"),
    ("47","LHG PUSH",        "PC7", "GPIOC","7"),
    ("73","LHG TRIG POS1  ★","PD13","GPIOD","13"),
    ("74","LHG TRIG POS2  ★","PD14","GPIOD","14"),
]

VIRTUAL = [
    ("77","Virtual A","—","GPIOF","PF3 (BTN57) + PF4 (BTN58)"),
    ("78","Virtual B","—","GPIOD","PD2 (BTN24) + PD4 (BTN26)"),
]
VIRTUAL_HDR = ["HID #", "Name", "GPIO Pin", "Port", "Source pins (active-low)"]

RHG = [
    ("48","RHG SW1",         "PB14","GPIOB","14"),
    ("49","RHG SW2",         "PB15","GPIOB","15"),
    ("50","RHG SW3",         "PC10","GPIOC","10"),
    ("51","RHG SW4",         "PC11","GPIOC","11"),
    ("52","RHG SW5",         "PC12","GPIOC","12"),
    ("53","RHG SW6",         "PC13","GPIOC","13"),
    ("54","RHG SW7",         "PF0", "GPIOF","0"),
    ("55","RHG HAT1 UP",     "PF1", "GPIOF","1"),
    ("56","RHG HAT1 DOWN",   "PF2", "GPIOF","2"),
    ("57","RHG HAT1 LEFT",   "PF3", "GPIOF","3"),
    ("58","RHG HAT1 RIGHT",  "PF4", "GPIOF","4"),
    ("59","RHG HAT2 UP",     "PF5", "GPIOF","5"),
    ("60","RHG HAT2 DOWN",   "PF6", "GPIOF","6"),
    ("61","RHG HAT2 LEFT",   "PG6", "GPIOG","6"),
    ("62","RHG HAT2 RIGHT",  "PG7", "GPIOG","7"),
    ("63","RHG TEMP A",      "PG8", "GPIOG","8"),
    ("64","RHG TEMP B",      "PG9", "GPIOG","9"),
    ("65","RHG 3POS1 A",     "PG10","GPIOG","10"),
    ("66","RHG 3POS1 B",     "PG11","GPIOG","11"),
    ("67","RHG 3POS2 A",     "PG12","GPIOG","12"),
    ("68","RHG 3POS2 B",     "PG13","GPIOG","13"),
    ("69","RHG PUSH",        "PG14","GPIOG","14"),
    ("70","TDU OFF",         "PG15","GPIOG","15"),
    ("71","SPARE 1",         "PF7", "GPIOF","7"),
    ("72","SPARE 2",         "PF8", "GPIOF","8"),
    ("75","RHG SW8",         "PG0", "GPIOG","0"),
    ("76","RHG SW9",         "PG1", "GPIOG","1"),
]

# ── GPIO Port Summary ──────────────────────────────────────────────────────────
PORT_SUMMARY = [
    ("GPIOA","PA2, PA3, PA6, PA7, PA11, PA12","ADC Z/Rx axes, ADC X/Y axes, USB DP/DM"),
    ("GPIOB","PB0–PB15",                        "LHG BTN 30–43, RHG BTN 48–49"),
    ("GPIOC","PC0, PC1, PC4–PC7, PC10–PC13",  "ADC Ry/Rz axes, LHG BTN 44–47, RHG BTN 50–53"),
    ("GPIOD","PD0–PD12, PD13–PD14",            "TDU BTN 17–21, LHG BTN 22–29, LHG BTN 73–74"),
    ("GPIOE","PE0–PE15",                        "TDU BTN 01–16"),
    ("GPIOF","PF0–PF8",                         "RHG BTN 54–60, Spare BTN 71–72"),
    ("GPIOG","PG0–PG1, PG6–PG15",               "RHG BTN 61–70, RHG BTN 75–76"),
]

# ── HID Report Format ──────────────────────────────────────────────────────────
REPORT_ROWS = [
    ("Bytes 0–11",  "6 analog axes",  "2 bytes each, signed 16-bit, little-endian",  "12 bytes"),
    ("Bytes 12–21", "76 physical + 2 virtual buttons + 2-bit padding", "1 bit per button, padded to 10 bytes", "10 bytes"),
    ("Total",       "—",              "No Report ID",                                  "22 bytes"),
]

# ── Page setup ─────────────────────────────────────────────────────────────────
PAGE_W, PAGE_H = A4
MARGIN = 16*mm

def on_first_page(canvas, doc):
    """Draw decorative header band on the title page."""
    canvas.saveState()
    canvas.setFillColor(C_TITLE)
    canvas.rect(0, PAGE_H - 42*mm, PAGE_W, 42*mm, fill=1, stroke=0)
    canvas.setFillColor(C_RULE)
    canvas.rect(0, PAGE_H - 44*mm, PAGE_W, 2*mm, fill=1, stroke=0)
    canvas.restoreState()

def on_later_pages(canvas, doc):
    """Header stripe + page number on continuation pages."""
    canvas.saveState()
    canvas.setFillColor(C_TITLE)
    canvas.rect(0, PAGE_H - 14*mm, PAGE_W, 14*mm, fill=1, stroke=0)
    canvas.setFillColor(C_RULE)
    canvas.rect(0, PAGE_H - 15.2*mm, PAGE_W, 1.2*mm, fill=1, stroke=0)

    # Running title
    canvas.setFillColor(colors.white)
    canvas.setFont("Helvetica-Bold", 9)
    canvas.drawString(MARGIN, PAGE_H - 9*mm, "TEDAC HID — Button Assignment Reference")
    canvas.setFont("Helvetica", 8)
    canvas.drawRightString(PAGE_W - MARGIN, PAGE_H - 9*mm,
                           f"Page {doc.page}")

    # Footer line
    canvas.setStrokeColor(C_RULE)
    canvas.setLineWidth(0.6)
    canvas.line(MARGIN, 10*mm, PAGE_W - MARGIN, 10*mm)
    canvas.setFillColor(C_TXT_MID)
    canvas.setFont("Helvetica", 7.5)
    canvas.drawString(MARGIN, 7*mm,
        "STM32H723ZGT6 · EC Buying FK723M1-ZGT6 · Active-low logic (GND = pressed) · Internal pull-up")
    canvas.drawRightString(PAGE_W - MARGIN, 7*mm, "76+2 buttons + 6 axes | v2.0")
    canvas.restoreState()

# ── Build document ─────────────────────────────────────────────────────────────
def build():
    doc = SimpleDocTemplate(
        OUTPUT,
        pagesize=A4,
        leftMargin=MARGIN,
        rightMargin=MARGIN,
        topMargin=46*mm,    # leave room for header band (first page uses more)
        bottomMargin=18*mm,
        title="TEDAC HID — Button Assignment Reference",
        author="TEDAC Project",
    )

    story = []

    # ── TITLE BLOCK ────────────────────────────────────────────────────────────
    story.append(Spacer(1, 28*mm))   # push below the dark band
    story.append(Paragraph("TEDAC HID", S_TITLE))
    story.append(Paragraph("Button Assignment Reference", S_SUBTITLE))
    story.append(Spacer(1, 3*mm))
    story.append(HRFlowable(width="60%", thickness=1.5, color=C_RULE,
                             hAlign="CENTER", spaceAfter=6))
    story.append(Paragraph(
        "MCU: STM32H723ZGT6 (LQFP144)  ·  Board: EC Buying FK723M1-ZGT6 V1.0",
        S_META))
    story.append(Paragraph(
        "76 physical + 2 virtual buttons  +  6 analog axes  ·  USB HID Custom — 22-byte report",
        S_META))
    story.append(Spacer(1, 10*mm))

    # ── QUICK STATS BOX ────────────────────────────────────────────────────────
    stats_data = [
        [
            Paragraph("<b>TDU</b><br/>21 buttons<br/>BTN 01–21", _stat_style(C_TDU_HDR)),
            Paragraph("<b>LHG</b><br/>28 buttons<br/>BTN 22–47, 73–74", _stat_style(C_LHG_HDR)),
            Paragraph("<b>RHG</b><br/>27 buttons<br/>BTN 48–72, 75–76", _stat_style(C_RHG_HDR)),
            Paragraph("<b>Total</b><br/>76+2 buttons<br/>+ 6 analog axes", _stat_style(C_AXS_HDR)),
        ]
    ]
    stats_t = Table(stats_data, colWidths=[43*mm]*4)
    stats_t.setStyle(TableStyle([
        ("BACKGROUND", (0,0),(0,0), C_TDU_HDR),
        ("BACKGROUND", (1,0),(1,0), C_LHG_HDR),
        ("BACKGROUND", (2,0),(2,0), C_RHG_HDR),
        ("BACKGROUND", (3,0),(3,0), C_AXS_HDR),
        ("TOPPADDING",    (0,0),(-1,-1), 10),
        ("BOTTOMPADDING", (0,0),(-1,-1), 10),
        ("ALIGN",         (0,0),(-1,-1), "CENTER"),
        ("VALIGN",        (0,0),(-1,-1), "MIDDLE"),
        ("LINEAFTER",     (0,0),(2,0),   0.5, colors.white),
        ("ROUNDEDCORNERS",[3]),
    ]))
    story.append(stats_t)
    story.append(Spacer(1, 6*mm))

    # Notes
    story.append(Paragraph(
        "★ Highlighted rows mark newly added buttons. "
        "Active-low logic: GND = button pressed. "
        "Internal pull-up on all GPIO inputs. "
        "78 button bits (76 physical + 2 virtual) + 2-bit padding = 10 bytes.",
        S_NOTE))

    story.append(PageBreak())

    # ══ ANALOG AXES ═══════════════════════════════════════════════════════════
    story.append(section_header(
        "Analog Axes  (ADC1 — Circular DMA)",
        "6 axes · signed 16-bit · –32 768 to +32 767  |  Potentiometers: 3V3 → wiper → GND",
        C_AXS_HDR))
    story.append(Spacer(1, 2*mm))
    story.append(_axes_table())
    story.append(Spacer(1, 6*mm))

    # ══ TDU ═══════════════════════════════════════════════════════════════════
    story.append(section_header(
        "TDU — Tactical Display Unit",
        "21 buttons  ·  BTN 01–21  ·  GPIOE (PE0–PE15) + GPIOD (PD8–PD12)",
        C_TDU_HDR))
    story.append(Spacer(1, 2*mm))
    story.append(btn_table(HDR, TDU, C_TDU_SUB, C_TDU_ROW1, C_TDU_ROW2))
    story.append(Spacer(1, 6*mm))

    # ══ LHG ═══════════════════════════════════════════════════════════════════
    story.append(section_header(
        "LHG — Left Hand Grip",
        "28 buttons  ·  BTN 22–47, 73–74  ·  GPIOD + GPIOB + GPIOC  ·  ★ = trigger (new)",
        C_LHG_HDR))
    story.append(Spacer(1, 2*mm))
    # highlight last 2 rows (index 26, 27 — the trigger buttons)
    story.append(btn_table(HDR, LHG, C_LHG_SUB, C_LHG_ROW1, C_LHG_ROW2,
                           highlight_rows={26, 27}))
    story.append(Paragraph(
        "★  BTN 73–74 (LHG TRIG POS1 / POS2) are the two detents of the LHG trigger. "
        "They share GPIOD with the existing LHG block and were added after the initial design.",
        S_NOTE))
    story.append(Spacer(1, 6*mm))

    # ══ RHG ═══════════════════════════════════════════════════════════════════
    story.append(section_header(
        "RHG — Right Hand Grip",
        "27 buttons  ·  BTN 48–72, 75–76  ·  GPIOB + GPIOC + GPIOF + GPIOG",
        C_RHG_HDR))
    story.append(Spacer(1, 2*mm))
    story.append(btn_table(HDR, RHG, C_RHG_SUB, C_RHG_ROW1, C_RHG_ROW2))
    story.append(Paragraph(
        "BTN 70 (TDU OFF) maps to the Off position of the TDU Day/NT/Off 3-position switch.  "
        "BTN 71–72 are spare/reserve inputs.  "
        "BTN 75–76 (RHG SW8/SW9) are additional normal buttons on PG0/PG1.",
        S_NOTE))
    story.append(Spacer(1, 6*mm))

    # ══ VIRTUAL BUTTONS ═══════════════════════════════════════════════════════
    story.append(section_header(
        "Virtual Buttons",
        "BTN 77–78  ·  Computed in firmware — no additional GPIO",
        C_SUBTITLE))
    story.append(Spacer(1, 2*mm))
    story.append(_virtual_table())
    story.append(Paragraph(
        "Virtual A (BTN 77): ON = bit 1 when PF3 AND PF4 are both NOT pressed.  "
        "virtual_A = !(PF3_pressed || PF4_pressed).  "
        "Virtual B (BTN 78): ON = bit 1 when PD2 AND PD4 are both NOT pressed.  "
        "virtual_B = !(PD2_pressed || PD4_pressed).  "
        "Physical buttons (BTN 01–76) are unaffected.",
        S_NOTE))
    story.append(Spacer(1, 6*mm))

    # ══ GPIO PORT SUMMARY ═════════════════════════════════════════════════════
    story.append(KeepTogether([
        section_header(
            "GPIO Port Summary",
            "All button inputs use GPIO_MODE_INPUT + GPIO_PULLUP",
            C_TITLE),
        Spacer(1, 2*mm),
        _port_summary_table(),
        Spacer(1, 6*mm),
    ]))

    # ══ HID REPORT FORMAT ═════════════════════════════════════════════════════
    story.append(KeepTogether([
        section_header(
            "USB HID Report Format",
            "Descriptor: 55 bytes  ·  Report: 22 bytes  ·  No Report ID",
            C_TITLE),
        Spacer(1, 2*mm),
        _report_table(),
        Spacer(1, 3*mm),
        Paragraph(
            "Byte layout: [0–11] 6×2-byte axes (signed 16-bit LE)  +  "
            "[12–21] 76 button bits (LSB first) + 4 padding bits.  "
            "Button reading: GPIO_PIN_RESET (LOW) = pressed = bit set to 1.",
            S_NOTE),
    ]))

    doc.build(story,
              onFirstPage=on_first_page,
              onLaterPages=on_later_pages)

    print(f"[OK] PDF generated: {OUTPUT}")


# ── Sub-table builders ─────────────────────────────────────────────────────────

def _stat_style(color):
    return ParagraphStyle("stat",
        fontSize=9, fontName="Helvetica-Bold",
        textColor=colors.white, alignment=TA_CENTER, leading=13)

def _axes_table():
    hdr_s = ParagraphStyle("th_ax",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_s  = ParagraphStyle("td_ax",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_sl = ParagraphStyle("td_axl",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_LEFT, leading=11)

    col_w = [18*mm, 52*mm, 20*mm, 22*mm, 18*mm + 52*mm - 52*mm]
    col_w = [18*mm, 52*mm, 20*mm, 22*mm, 30*mm]

    data = [[Paragraph(h, hdr_s) for h in AXES_HDR]]
    for i, r in enumerate(AXES):
        data.append([
            Paragraph(r[0], td_s),
            Paragraph(r[1], td_sl),
            Paragraph(r[2], td_s),
            Paragraph(r[3], td_s),
            Paragraph(r[4], td_s),
        ])
    t = Table(data, colWidths=col_w)
    t.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0), C_COL_HDR),
        ("LINEBELOW",     (0,0), (-1,0), 1.2, C_AXS_HDR),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [C_AXS_ROW1, C_AXS_ROW2]),
        ("GRID",          (0,0), (-1,-1), 0.4, colors.HexColor("#D0D8E4")),
        ("TOPPADDING",    (0,0), (-1,-1), 4),
        ("BOTTOMPADDING", (0,0), (-1,-1), 4),
        ("LEFTPADDING",   (0,0), (-1,-1), 5),
        ("RIGHTPADDING",  (0,0), (-1,-1), 5),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
    ]))
    return t


def _port_summary_table():
    hdr_s = ParagraphStyle("th_p",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_s  = ParagraphStyle("td_p",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_sm = ParagraphStyle("td_pm",
        fontSize=8, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_LEFT, leading=11)

    col_w = [20*mm, 52*mm, 100*mm]
    headers = ["Port", "Pins Used", "Function"]
    data = [[Paragraph(h, hdr_s) for h in headers]]
    row_colors = [
        colors.HexColor("#EBF3FB"),  # A - light blue
        colors.HexColor("#EAFAF1"),  # B - light green
        colors.HexColor("#EAFAF1"),  # C - light green
        colors.HexColor("#EBF3FB"),  # D - light blue (has new pins)
        colors.HexColor("#EBF3FB"),  # E - light blue
        colors.HexColor("#FEF3E2"),  # F - light amber
        colors.HexColor("#FEF3E2"),  # G - light amber
    ]
    for i, r in enumerate(PORT_SUMMARY):
        data.append([
            Paragraph(r[0], td_s),
            Paragraph(r[1], td_sm),
            Paragraph(r[2], td_sm),
        ])
    t = Table(data, colWidths=col_w)
    ts = TableStyle([
        ("BACKGROUND",    (0,0), (-1,0), C_COL_HDR),
        ("LINEBELOW",     (0,0), (-1,0), 1.2, C_TITLE),
        ("GRID",          (0,0), (-1,-1), 0.4, colors.HexColor("#D0D8E4")),
        ("TOPPADDING",    (0,0), (-1,-1), 4),
        ("BOTTOMPADDING", (0,0), (-1,-1), 4),
        ("LEFTPADDING",   (0,0), (-1,-1), 5),
        ("RIGHTPADDING",  (0,0), (-1,-1), 5),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
    ])
    for i, rc in enumerate(row_colors):
        ts.add("BACKGROUND", (0, i+1), (-1, i+1), rc)
    # Highlight the GPIOD row (index 3) since it has the new pins
    ts.add("FONTNAME", (0, 4), (-1, 4), "Helvetica-Bold")
    ts.add("BACKGROUND", (0, 4), (-1, 4), C_LHG_NEW)
    t.setStyle(ts)
    return t


def _report_table():
    hdr_s = ParagraphStyle("th_r",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_sc = ParagraphStyle("td_rc",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_sl = ParagraphStyle("td_rl",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_LEFT, leading=11)

    col_w = [28*mm, 58*mm, 72*mm, 24*mm]
    headers = ["Bytes", "Content", "Notes", "Size"]
    data = [[Paragraph(h, hdr_s) for h in headers]]
    rcolors = [C_AXS_ROW1, C_LHG_ROW1, colors.HexColor("#F0F4FF")]
    for i, r in enumerate(REPORT_ROWS):
        data.append([
            Paragraph(r[0], td_sc),
            Paragraph(r[1], td_sl),
            Paragraph(r[2], td_sl),
            Paragraph(r[3], td_sc),
        ])
    t = Table(data, colWidths=col_w)
    ts = TableStyle([
        ("BACKGROUND",    (0,0), (-1,0), C_COL_HDR),
        ("LINEBELOW",     (0,0), (-1,0), 1.2, C_TITLE),
        ("GRID",          (0,0), (-1,-1), 0.4, colors.HexColor("#D0D8E4")),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
        ("LEFTPADDING",   (0,0), (-1,-1), 5),
        ("RIGHTPADDING",  (0,0), (-1,-1), 5),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        # Last row (Total) bold
        ("FONTNAME",      (0,3), (-1,3), "Helvetica-Bold"),
        ("BACKGROUND",    (0,3), (-1,3), colors.HexColor("#E8EDF7")),
    ])
    for i, rc in enumerate(rcolors):
        ts.add("BACKGROUND", (0, i+1), (-1, i+1), rc)
    t.setStyle(ts)
    return t


def _virtual_table():
    hdr_s = ParagraphStyle("th_v",
        fontSize=8.5, fontName="Helvetica-Bold",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_c = ParagraphStyle("td_vc",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_CENTER, leading=11)
    td_l = ParagraphStyle("td_vl",
        fontSize=8.5, fontName="Helvetica",
        textColor=C_TXT_DARK, alignment=TA_LEFT, leading=11)

    col_w = [18*mm, 22*mm, 20*mm, 20*mm, 92*mm]
    data = [[Paragraph(h, hdr_s) for h in VIRTUAL_HDR]]
    row_colors = [C_TDU_ROW1, C_TDU_ROW2]
    for i, r in enumerate(VIRTUAL):
        data.append([
            Paragraph(r[0], td_c),
            Paragraph(r[1], td_c),
            Paragraph(r[2], td_c),
            Paragraph(r[3], td_c),
            Paragraph(r[4], td_l),
        ])
    t = Table(data, colWidths=col_w)
    ts = TableStyle([
        ("BACKGROUND",    (0,0), (-1,0), C_COL_HDR),
        ("LINEBELOW",     (0,0), (-1,0), 1.2, C_SUBTITLE),
        ("GRID",          (0,0), (-1,-1), 0.4, colors.HexColor("#D0D8E4")),
        ("TOPPADDING",    (0,0), (-1,-1), 4),
        ("BOTTOMPADDING", (0,0), (-1,-1), 4),
        ("LEFTPADDING",   (0,0), (-1,-1), 5),
        ("RIGHTPADDING",  (0,0), (-1,-1), 5),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
    ])
    for i, rc in enumerate(row_colors):
        ts.add("BACKGROUND", (0, i+1), (-1, i+1), rc)
    t.setStyle(ts)
    return t


if __name__ == "__main__":
    build()
