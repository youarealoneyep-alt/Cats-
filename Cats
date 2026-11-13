<!DOCTYPE html>
<html lang="ru">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>🐾 Котоквест — типы кошек</title>
<style>
  :root{
    --orange:#f97316;
    --orange-dark:#ea580c;
    --purple:#7c3aed;
    --green:#16a34a;
    --red:#dc2626;
    --ink:#3b2a20;
    --muted:#8a7566;
    --card:#fffdf9;
  }
  *{box-sizing:border-box;margin:0;padding:0;}
  html,body{min-height:100%;}
  body{
    font-family:'Segoe UI',system-ui,-apple-system,'Helvetica Neue',sans-serif;
    background:
      radial-gradient(circle at 12% 12%, #fff4e9 0%, transparent 45%),
      radial-gradient(circle at 88% 88%, #ffdcc2 0%, transparent 50%),
      linear-gradient(135deg,#ffe9d6 0%,#f7c9a8 100%);
    min-height:100vh;
    display:flex;align-items:center;justify-content:center;
    padding:18px;color:var(--ink);
    position:relative;overflow-x:hidden;
  }

  /* Плавающие лапки на фоне */
  .bg-paw{
    position:fixed;font-size:34px;opacity:.14;pointer-events:none;
    animation:float 9s ease-in-out infinite;user-select:none;
  }
  @keyframes float{
    0%,100%{transform:translateY(0) rotate(-8deg);}
    50%{transform:translateY(-26px) rotate(8deg);}
  }

  .game{
    width:100%;max-width:640px;
    background:var(--card);
    border-radius:26px;
    padding:26px 24px 28px;
    box-shadow:0 24px 60px -18px rgba(120,70,30,.45), 0 0 0 1px rgba(255,255,255,.8) inset;
    position:relative;z-index:2;
    animation:pop .45s cubic-bezier(.34,1.56,.64,1);
  }
  @keyframes pop{
    from{opacity:0;transform:scale(.94) translateY(14px);}
    to{opacity:1;transform:scale(1) translateY(0);}
  }

  /* ---- Прогресс ---- */
  .progress-wrap{
    display:flex;align-items:center;gap:12px;margin-bottom:20px;
  }
  .progress-track{
    flex:1;height:11px;border-radius:99px;background:#f0e2d4;overflow:hidden;
    box-shadow:inset 0 1px 3px rgba(0,0,0,.08);
  }
  .progress-bar{
    height:100%;width:0%;border-radius:99px;
    background:linear-gradient(90deg,var(--orange),#fbbf24);
    transition:width .5s cubic-bezier(.4,0,.2,1);
  }
  .progress-text{
    font-size:13px;font-weight:700;color:var(--muted);white-space:nowrap;
    font-variant-numeric:tabular-nums;
  }

  /* ---- Стартовый экран ---- */
  .hero{text-align:center;padding:6px 4px 2px;}
  .hero-emoji{
    font-size:74px;line-height:1;display:block;margin-bottom:12px;
    animation:bounce 2.2s ease-in-out infinite;
  }
  @keyframes bounce{
    0%,100%{transform:translateY(0) rotate(-3deg);}
    50%{transform:translateY(-12px) rotate(3deg);}
  }
  .hero h1{
    font-size:30px;line-height:1.15;margin-bottom:12px;
    background:linear-gradient(120deg,var(--orange-dark),var(--purple));
    -webkit-background-clip:text;background-clip:text;color:transparent;
  }
  .hero p{font-size:16px;line-height:1.55;color:var(--muted);margin-bottom:24px;}

  /* ---- Вопросы ---- */
  .q-counter{
    display:inline-block;font-size:12px;font-weight:800;letter-spacing:.06em;
    text-transform:uppercase;color:var(--purple);
    background:#f3ecff;padding:6px 12px;border-radius:99px;margin-bottom:14px;
  }
  .q-emoji{font-size:46px;line-height:1;display:block;margin-bottom:10px;}
  .q-text{
    font-size:19px;line-height:1.45;font-weight:700;margin-bottom:20px;
  }

  .options{display:flex;flex-direction:column;gap:10px;}

  .option{
    font:inherit;font-size:16px;font-weight:600;text-align:left;
    padding:15px 18px;border-radius:16px;cursor:pointer;
    background:#fff;color:var(--ink);
    border:2px solid #f0e2d4;
    transition:transform .15s ease, border-color .15s, background .2s, box-shadow .15s;
    display:flex;align-items:center;gap:12px;
  }
  .option::before{
    content:"";width:22px;height:22px;flex:0 0 22px;border-radius:50%;
    border:2px solid #e2cdba;transition:.2s;
  }
  .option:hover:not(:disabled){
    transform:translateY(-2px);
    border-color:var(--orange);
    box-shadow:0 8px 18px -8px rgba(249,115,22,.6);
  }
  .option:hover:not(:disabled)::before{border-color:var(--orange);}
  .option:disabled{cursor:default;}

  .option.correct{
    background:#e8f9ee;border-color:var(--green);color:#14532d;
    animation:pulse .45s ease;
  }
  .option.correct::before{
    background:var(--green);border-color:var(--green);
    content:"✓";color:#fff;font-size:13px;display:grid;place-items:center;
  }
  .option.wrong{
    background:#fdeaea;border-color:var(--red);color:#7f1d1d;
    animation:shake .4s ease;
  }
  .option.wrong::before{
    background:var(--red);border-color:var(--red);
    content:"✕";color:#fff;font-size:13px;display:grid;place-items:center;
  }
  @keyframes pulse{0%{transform:scale(1);}50%{transform:scale(1.03);}100%{transform:scale(1);}}
  @keyframes shake{
    0%,100%{transform:translateX(0);}
    20%{transform:translateX(-7px);}
    40%{transform:translateX(7px);}
    60%{transform:translateX(-5px);}
    80%{transform:translateX(5px);}
  }

  /* ---- Обратная связь ---- */
  .feedback{
    margin-top:16px;padding:14px 16px;border-radius:14px;
    font-size:14.5px;line-height:1.5;
    background:#f6f1ea;border-left:5px solid var(--purple);
    animation:fadeUp .35s ease;
  }
  .feedback b{color:var(--purple);}
  @keyframes fadeUp{
    from{opacity:0;transform:translateY(8px);}
    to{opacity:1;transform:translateY(0);}
  }

  /* ---- Кнопки ---- */
  .btn{
    font:inherit;font-size:17px;font-weight:800;cursor:pointer;
    border:none;border-radius:16px;padding:15px 26px;
    color:#fff;background:linear-gradient(135deg,var(--orange),var(--orange-dark));
    box-shadow:0 12px 24px -10px rgba(234,88,12,.85);
    transition:transform .15s ease, box-shadow .15s;
    display:inline-flex;align-items:center;gap:8px;
  }
  .btn:hover{transform:translateY(-2px);box-shadow:0 16px 28px -10px rgba(234,88,12,.9);}
  .btn:active{transform:translateY(1px) scale(.99);}
  .btn.center{display:flex;margin:22px auto 0;}

  .btn-ghost{
    background:#fff;color:var(--orange-dark);
    border:2px solid #f3d3b6;box-shadow:none;
    font-size:15px;padding:12px 22px;
  }
  .btn-ghost:hover{background:#fff7ef;box-shadow:none;}

  /* ---- Результат ---- */
  .result{text-align:center;}
  .result-emoji{font-size:80px;line-height:1;display:block;margin-bottom:10px;animation:bounce 2.4s ease-in-out infinite;}
  .result-title{
    font-size:27px;margin-bottom:10px;
    background:linear-gradient(120deg,var(--orange-dark),var(--purple));
    -webkit-background-clip:text;background-clip:text;color:transparent;
  }
  .result-score{
    font-size:15px;font-weight:700;color:var(--muted);margin-bottom:6px;
  }
  .score-big{
    font-size:46px;font-weight:900;color:var(--orange-dark);
    line-height:1;margin-bottom:14px;font-variant-numeric:tabular-nums;
  }
  .result-desc{
    font-size:16px;line-height:1.55;color:var(--muted);
    max-width:440px;margin:0 auto 8px;
  }

  @media (max-width:480px){
    .game{padding:20px 16px 22px;border-radius:20px;}
    .hero h1{font-size:24px;}
    .q-text{font-size:17px;}
    .option{font-size:15px;padding:13px 14px;}
    .q-emoji{font-size:38px;}
    .result-title{font-size:22px;}
  }
</style>
</head>
<body>

<div class="game">
  <div class="progress-wrap" id="progressWrap">
    <div class="progress-track"><div class="progress-bar" id="progressBar"></div></div>
    <span class="progress-text" id="progressText">1 / 7</span>
  </div>
  <div id="app"></div>
</div>

<script>
/* =========================================================
   ДАННЫЕ КВЕСТА
   ========================================================= */
const questions = [
  {
    emoji: "🛁",
    q: "У этой породы совсем нет шерсти — только тёплая бархатистая кожа, которую нужно беречь от солнца и сквозняков.",
    options: ["Канадский сфинкс", "Мейн-кун", "Персидская", "Курильский бобтейл"],
    correct: 0,
    fact: "Канадский сфинкс — результат естественной мутации. Кожа у него на ощупь как персик и всегда тёплая, а морщинки на теле — фирменный знак породы."
  },
  {
    emoji: "🦁",
    q: "Настоящий гигант среди домашних кошек: самцы могут весить до 12 кг, а шерсть на шее образует пышный «воротник», как у маленького льва.",
    options: ["Британская короткошёрстная", "Мейн-кун", "Манчкин", "Русская голубая"],
    correct: 1,
    fact: "Мейн-кун — самая крупная домашняя порода. Родом она из американского штата Мэн, а ещё мейн-куны обожают воду и умеют «разговаривать» забавным курлыканьем."
  },
  {
    emoji: "📏",
    q: "У этих кошек очень короткие лапки, но это не мешает им быть ловкими и быстрыми. В шутку породу называют «кошкой-такса».",
    options: ["Шотландская вислоухая", "Девон-рекс", "Манчкин", "Абиссинская"],
    correct: 2,
    fact: "Манчкин — порода с генетической мутацией, из-за которой лапы остаются короткими. Несмотря на это, манчкины отлично прыгают и обожают играть."
  },
  {
    emoji: "🏴",
    q: "Ушки этой кошки загнуты вперёд и вниз, поэтому мордочка кажется круглой и вечно удивлённой. Порода родом из Шотландии.",
    options: ["Сфинкс", "Бенгальская", "Сибирская", "Шотландская вислоухая"],
    correct: 3,
    fact: "Шотландская вислоухая (скоттиш-фолд) обязана своим видом мутации хрящей ушей. Такие кошки спокойны, ласковы и очень привязаны к хозяину."
  },
  {
    emoji: "🐆",
    q: "Окрас этой породы напоминает миниатюрного леопарда, а сама кошка обожает воду и часто играет с ней в раковине.",
    options: ["Бенгальская", "Турецкая ангора", "Абиссинская", "Мейн-кун"],
    correct: 0,
    fact: "Бенгальская кошка была выведена скрещиванием домашней кошки с азиатской леопардовой. Пятна и «розетки» на шерсти — природный рисунок, а вода для неё — любимая стихия."
  },
  {
    emoji: "👑",
    q: "Одна из самых древних и узнаваемых пород: длинная пушистая шерсть, приплюснутая мордочка и очень спокойный, флегматичный характер.",
    options: ["Норвежская лесная", "Персидская", "Русская голубая", "Сибирская"],
    correct: 1,
    fact: "Персидская кошка известна со времён Древнего Востока. Её длинная шерсть требует ежедневного расчёсывания, зато характер — мягкий и невозмутимый."
  },
  {
    emoji: "💙",
    q: "Серебристо-голубая шерсть с нежным отливом, яркие зелёные глаза и грациозный силуэт. Эта порода родом из России.",
    options: ["Британская короткошёрстная", "Шартрез", "Русская голубая", "Корат"],
    correct: 2,
    fact: "Русская голубая — одна из самых элегантных пород. У неё двойная шерсть с серебристым «типпингом», зелёные глаза и деликатный, тихий характер."
  }
];

/* =========================================================
   СОСТОЯНИЕ ИГРЫ
   ========================================================= */
const state = { index: 0, score: 0, answered: false };

const app          = document.getElementById('app');
const progressBar  = document.getElementById('progressBar');
const progressText = document.getElementById('progressText');
const progressWrap = document.getElementById('progressWrap');

/* =========================================================
   ФОНОВЫЕ ЛАПКИ
   ========================================================= */
(function createPaws(){
  const paws = ['🐾','🐾','🐾','🐈','🐾','🐈‍⬛'];
  const positions = [
    {top:'8%',  left:'5%'},  {top:'18%', right:'7%'},
    {top:'62%', left:'8%'},  {top:'78%', right:'10%'},
    {top:'42%', right:'4%'}, {top:'88%', left:'22%'}
  ];
  positions.forEach((pos, i) => {
    const el = document.createElement('div');
    el.className = 'bg-paw';
    el.textContent = paws[i % paws.length];
    Object.assign(el.style, pos);
    el.style.animationDelay = (i * 0.9) + 's';
    el.style.fontSize = (26 + (i % 3) * 10) + 'px';
    document.body.appendChild(el);
  });
})();

/* =========================================================
   УТИЛИТЫ
   ========================================================= */
function updateProgress(current, total){
  const pct = total ? (current / total) * 100 : 0;
  progressBar.style.width = pct + '%';
  progressText.textContent = Math.min(current + 1, total) + ' / ' + total;
}

/* =========================================================
   СТАРТОВЫЙ ЭКРАН
   ========================================================= */
function showStart(){
  progressWrap.style.display = 'none';
  app.innerHTML = `
    <div class="hero">
      <span class="hero-emoji">🐱</span>
      <h1>Котоквест:<br>типы кошек</h1>
      <p>Добро пожаловать в кошачью академию!<br>
         Тебя ждут 7 вопросов о породах и типах кошек.
         Отвечай, узнавай новое и получи звание настоящего котолога.</p>
      <button class="btn center" id="startBtn">Начать квест 🐾</button>
    </div>
  `;
  document.getElementById('startBtn').addEventListener('click', () => {
    state.index = 0;
    state.score = 0;
    state.answered = false;
    progressWrap.style.display = 'flex';
    showQuestion();
  });
}

/* =========================================================
   ЭКРАН ВОПРОСА
   ========================================================= */
function showQuestion(){
  state.answered = false;
  const q = questions[state.index];
  updateProgress(state.index, questions.length);

  app.innerHTML = `
    <div class="question-card">
      <span class="q-counter">Вопрос ${state.index + 1} из ${questions.length}</span>
      <span class="q-emoji">${q.emoji}</span>
      <h2 class="q-text">${q.q}</h2>
      <div class="options" id="options">
        ${q.options.map((opt, i) =>
          `<button class="option" data-index="${i}">${opt}</button>`
        ).join('')}
      </div>
      <div id="feedbackSlot"></div>
    </div>
  `;

  app.querySelectorAll('.option').forEach(btn => {
    btn.addEventListener('click', () => handleAnswer(Number(btn.dataset.index)));
  });
}

/* =========================================================
   ОБРАБОТКА ОТВЕТА
   ========================================================= */
function handleAnswer(selected){
  if (state.answered) return;
  state.answered = true;

  const q = questions[state.index];
  const isCorrect = selected === q.correct;
  if (isCorrect) state.score++;

  const buttons = app.querySelectorAll('.option');
  buttons.forEach((btn, i) => {
    btn.disabled = true;
    if (i === q.correct) btn.classList.add('correct');
    if (i === selected && !isCorrect) btn.classList.add('wrong');
  });

  const feedbackSlot = document.getElementById('feedbackSlot');
  const isLast = state.index === questions.length - 1;

  feedbackSlot.innerHTML = `
    <div class="feedback">
      <b>${isCorrect ? '✅ Верно!' : '❌ Не совсем.'}</b>
      ${q.fact}
    </div>
    <button class="btn center" id="nextBtn">
      ${isLast ? 'Показать результат 🏆' : 'Дальше →'}
    </button>
  `;

  document.getElementById('nextBtn').addEventListener('click', () => {
    state.index++;
    if (state.index < questions.length) {
      showQuestion();
    } else {
      showResult();
    }
  });
}

/* =========================================================
   ЭКРАН РЕЗУЛЬТАТА
   ========================================================= */
function showResult(){
  progressWrap.style.display = 'none';

  const total = questions.length;
  const pct = state.score / total;

  let emoji, title, desc;
  if (pct === 1) {
    emoji = '🐱👑';
    title = 'Повелитель котов';
    desc = 'Безупречно! Ты знаешь о породах кошек всё. Даже самые гордые мурлыки аплодируют тебе лапками.';
  } else if (pct >= 0.8) {
    emoji = '😺';
    title = 'Знаток пород';
    desc = 'Отличный результат! Лишь пара котов смогла тебя запутать — но ты почти эксперт.';
  } else if (pct >= 0.6) {
    emoji = '😸';
    title = 'Начинающий котолог';
    desc = 'Неплохо! Ты уже неплохо разбираешься в кошках, но есть куда расти. Читай и возвращайся!';
  } else if (pct >= 0.4) {
    emoji = '🐾';
    title = 'Котёнок-исследователь';
    desc = 'Ты только начинаешь знакомство с миром кошек. Каждый кот — это открытие. Всё ещё впереди!';
  } else {
    emoji = '🐈';
    title = 'Друг всех мурлык';
    desc = 'Главное — не названия пород, а любовь к кошкам. А она у тебя точно есть. Попробуй ещё раз!';
  }

  app.innerHTML = `
    <div class="result">
      <span class="result-emoji">${emoji}</span>
      <h2 class="result-title">${title}</h2>
      <div class="result-score">Правильных ответов</div>
      <div class="score-big">${state.score} / ${total}</div>
      <p class="result-desc">${desc}</p>
      <button class="btn center" id="restartBtn">Пройти ещё раз 🔄</button>
      <button class="btn btn-ghost center" id="homeBtn">На главную 🏠</button>
    </div>
  `;

  document.getElementById('restartBtn').addEventListener('click', () => {
    state.index = 0;
    state.score = 0;
    state.answered = false;
    progressWrap.style.display = 'flex';
    showQuestion();
  });

  document.getElementById('homeBtn').addEventListener('click', showStart);

  if (pct >= 0.8) celebrate();
}

/* =========================================================
   НЕБОЛЬШОЙ ПРАЗДНИК ПРИ ХОРОШЕМ РЕЗУЛЬТАТЕ
   ========================================================= */
function celebrate(){
  const emojis = ['🐾','⭐','🐱','✨','🐈','💛'];
  for (let i = 0; i < 26; i++) {
    const el = document.createElement('div');
    el.textContent = emojis[Math.floor(Math.random() * emojis.length)];
    el.style.cssText = `
      position:fixed;
      left:${Math.random() * 100}vw;
      top:-40px;
      font-size:${16 + Math.random() * 22}px;
      pointer-events:none;
      z-index:9999;
      transition:transform ${1.6 + Math.random() * 1.4}s linear, opacity 2.4s ease;
    `;
    document.body.appendChild(el);
    requestAnimationFrame(() => {
      el.style.transform = `translateY(${window.innerHeight + 120}px) rotate(${Math.random() * 720 - 360}deg)`;
      el.style.opacity = '0';
    });
    setTimeout(() => el.remove(), 3200);
  }
}

/* =========================================================
   ЗАПУСК
   ========================================================= */
showStart();
</script>
</body>
</html>
