(window["webpackJsonp"]=window["webpackJsonp"]||[]).push([["chunk-75c58ff7"],{"0af1":function(e,t,n){"use strict";n.d(t,"d",(function(){return a})),n.d(t,"c",(function(){return c})),n.d(t,"a",(function(){return o})),n.d(t,"e",(function(){return u})),n.d(t,"f",(function(){return i})),n.d(t,"b",(function(){return s}));n("99af");var r=n("1f75"),a=function(e){return r["a"].get("/plugins",{status:e})},c=function(e){return r["a"].get("/plugins/".concat(e))},o=function(e){var t=new FormData;return t.append("plugin",e),r["a"].post("/plugins/install",t)},u=function(e){return r["a"].delete("/plugins/".concat(e))},i=function(e,t){return r["a"].put("/plugins/".concat(e,"/").concat(t))},s=function(e,t){return r["a"].post("/plugins/".concat(e,"/move"),{position:t})}},"0d47":function(e,t,n){"use strict";var r=n("5530"),a=(n("b0c0"),n("7a23")),c=n("e9b3"),o=n("6c02"),u=Object(a["defineComponent"])({name:"DetailHeader"}),i=Object(a["defineComponent"])(Object(r["a"])(Object(r["a"])({},u),{},{props:{item:{required:!0,type:Object}},setup:function(e){var t=e,n=Object(o["f"])(),r=function(){var e=t.item,r=e.routeName,a=e.path,c=e.backFunc,o=e.route;o?n.push(o):a?n.push({path:a}):r?n.push({name:r}):c&&c()};return function(t,n){var o=Object(a["resolveComponent"])("el-page-header");return Object(a["openBlock"])(),Object(a["createBlock"])(o,{class:"detail-header",icon:Object(a["unref"])(c["a"]),content:e.item.name,onBack:r},Object(a["createSlots"])({_:2},[t.$slots.content?{name:"content",fn:Object(a["withCtx"])((function(){return[Object(a["renderSlot"])(t.$slots,"content")]}))}:void 0]),1032,["icon","content"])}}}));n("de52");const s=i;t["a"]=s},"1f75":function(e,t,n){"use strict";var r=n("1da1"),a=(n("96cf"),n("d3b7"),n("6062"),n("3ca3"),n("ddb0"),n("caad"),n("2532"),n("99af"),n("25f0"),n("cee4")),c=n("2295"),o=n("5530"),u=(n("a9e3"),n("b680"),n("159b"),n("3ef4")),i=n("e466"),s=n("2ef0"),l=n.n(s),d=25,f=function(e){var t=1e3*Number((e.length/d).toFixed(3));return t<3e3?3e3:t>8e3?8e3:t},p=function(e){var t=!e||Object(s["isString"])(e)||Object(s["isFunction"])(e)?{message:e}:e;return t},b=function(e){var t=p(e),n=t.message,r=t.duration,a=t.showClose,c=t.type,i=r||n&&f(n)||void 0,s=a||"error"===c,l=Object(u["a"])(Object(o["a"])(Object(o["a"])({},e),{},{duration:i,showClose:s}));return window.setTimeout((function(){var e;return null===l||void 0===l||null===(e=l.close)||void 0===e?void 0:e.call(l)}),i?i+2e3:8e3),l};i["d"].forEach((function(e){b[e]=function(){var t=arguments.length>0&&void 0!==arguments[0]?arguments[0]:{},n=p(t);return b(Object(o["a"])(Object(o["a"])({},n),{},{type:e}))}}));var v=b,O=n("323e"),m=n.n(O),j=(n("a5d8"),n("afbc")),g=n("0613"),h=n("2fc2"),w="BAD_TOKEN",k="TOKEN_TIME_OUT",E="BAD_USERNAME_OR_PWD",_=n("88c3");m.a.configure({showSpinner:!1,trickleSpeed:200});var C=new Set,x=function(){return C=new Set};Object.assign(a["a"].defaults,{baseURL:h["b"],timeout:2e4}),a["a"].interceptors.request.use((function(e){var t=g["a"].state.user;e.headers={Authorization:"Bearer "+t.token};var n=new AbortController;return e.signal=n.signal,e.controller=n,g["a"].commit("ADD_ABORT_CONTROLLER",n),e}),(function(e){Promise.reject(e)})),a["a"].interceptors.request.use(function(){var e=Object(r["a"])(regeneratorRuntime.mark((function e(t){return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:if(t.doNotTriggerProgress){e.next=4;break}return g["a"].state.request_queue||m.a.start(),e.next=4,g["a"].dispatch("SET_REQ_CHANGE",!0);case 4:return e.abrupt("return",t);case 5:case"end":return e.stop()}}),e)})));return function(t){return e.apply(this,arguments)}}());var N=function(e,t){return 401===e&&[w,k].includes(t.code)},R=function(){var e=Object(r["a"])(regeneratorRuntime.mark((function e(t){var n;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return e.prev=0,e.next=3,t.text();case 3:return n=e.sent,e.abrupt("return",JSON.parse(n));case 7:return e.prev=7,e.t0=e["catch"](0),e.abrupt("return",{});case 10:case"end":return e.stop()}}),e,null,[[0,7]])})));return function(t){return e.apply(this,arguments)}}();function B(){return T.apply(this,arguments)}function T(){return T=Object(r["a"])(regeneratorRuntime.mark((function e(){var t;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return e.next=2,g["a"].dispatch("SET_REQ_CHANGE",!1);case 2:t=g["a"].state.request_queue,t>0?m.a.inc():m.a.done();case 4:case"end":return e.stop()}}),e)}))),T.apply(this,arguments)}a["a"].interceptors.response.use((function(e){if(e.config.doNotTriggerProgress||B(),e.data instanceof Blob)return e;var t=e.config.controller;return g["a"].commit("REMOVE_ABORT_CONTROLLER",t),e.data||e.status}),function(){var e=Object(r["a"])(regeneratorRuntime.mark((function e(t){var n,r,a,o,u,i,s,d,f,p,b;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:if(t.config.doNotTriggerProgress||B(),!t.response){e.next=20;break}if(!(t.response.data instanceof Blob)){e.next=6;break}return e.next=5,R(t.response.data);case 5:t.response.data=e.sent;case 6:if(n=t.response,r=n.data,a=n.status,C.has(a)){e.next=18;break}if(C.add(a),u=401===a&&g["a"].state.afterCurrentUserPwdChanged,!N(a,r)){e.next=15;break}return u?g["a"].commit("SET_AFTER_CURRENT_USER_PWD_CHANGED",!1):c["a"].error(_["a"].global.t("Base.tokenExpiredMsg")),Object(j["c"])(),window.setTimeout(x,1e3),e.abrupt("return",Promise.reject(t));case 15:i=(null===(o=t.config)||void 0===o?void 0:o.errorsHandleCustom)&&Array.isArray(t.config.errorsHandleCustom)&&t.config.errorsHandleCustom.includes(a),i||((null===r||void 0===r?void 0:r.code)===E?c["a"].error(_["a"].global.t("Base.namePwdError")):null!==r&&void 0!==r&&r.code||null!==r&&void 0!==r&&r.message?v.error("".concat(a," ").concat(null!==(s=null===r||void 0===r?void 0:r.code)&&void 0!==s?s:"",": ").concat(null!==(d=null===r||void 0===r||null===(f=r.message)||void 0===f?void 0:f.toString())&&void 0!==d?d:"")):v.error(a+" Network error")),401===a&&Object(j["c"])();case 18:e.next=24;break;case 20:if(p=t.code===h["F"]&&t.config.handleTimeoutSelf,"ERR_CANCELED"!==t.code||"canceled"!==t.message){e.next=23;break}return e.abrupt("return");case 23:C.has(0)||(p||v.error(_["a"].global.t("Base.networkError")),C.add(0));case 24:return 0===g["a"].state.request_queue&&(C=new Set),l.a.throttle(x,2e3,{trailing:!1}),b=t.config.controller,g["a"].commit("REMOVE_ABORT_CONTROLLER",b),e.abrupt("return",Promise.reject(t));case 29:case"end":return e.stop()}}),e)})));return function(t){return e.apply(this,arguments)}}());t["a"]=a["a"]},"2f4f":function(e,t,n){"use strict";n.r(t);var r=n("1da1"),a=(n("96cf"),n("99af"),n("b0c0"),n("7a23")),c=n("47e2"),o=n("6c02"),u=n("3ef4"),i=n("a90d"),s=n("0af1"),l=n("0d47"),d={class:"plugin-install app-wrapper"},f={key:0},p={class:"upload-placeholder"},b={key:1,class:"file-name"},v={class:"upload-tip"},O={class:"btns"},m=Object(a["defineComponent"])({setup:function(e){var t=Object(o["f"])(),n=Object(c["b"])(),m=n.t,j=function(e){var t=arguments.length>1&&void 0!==arguments[1]?arguments[1]:"Plugins";return m("".concat(t,".").concat(e))},g=Object(a["ref"])(!1),h=function(){return t.push({name:"plugins"})},w=Object(a["ref"])(void 0),k=Object(a["computed"])((function(){return w.value&&w.value.name?[w]:[]})),E=function(e){return w.value=e,!1},_=function(){var e=Object(r["a"])(regeneratorRuntime.mark((function e(){return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:if(w.value){e.next=3;break}return u["a"].error(j("uploadWarning")),e.abrupt("return");case 3:return e.prev=3,g.value=!0,e.next=7,Object(s["a"])(w.value);case 7:u["a"].success(j("successfulInstallation")),t.push({name:"plugins"}),e.next=14;break;case 11:e.prev=11,e.t0=e["catch"](3),console.error(e.t0);case 14:return e.prev=14,g.value=!1,e.finish(14);case 17:case"end":return e.stop()}}),e,null,[[3,11,14,17]])})));return function(){return e.apply(this,arguments)}}();return function(e,t){var n=Object(a["resolveComponent"])("el-icon"),r=Object(a["resolveComponent"])("el-upload"),c=Object(a["resolveComponent"])("el-button"),o=Object(a["resolveComponent"])("el-card");return Object(a["openBlock"])(),Object(a["createElementBlock"])("div",d,[Object(a["createVNode"])(l["a"],{item:{name:j("installPlugin"),path:"/plugins"}},null,8,["item"]),Object(a["createVNode"])(o,{class:"app-card plugin-install-card"},{default:Object(a["withCtx"])((function(){return[Object(a["createVNode"])(r,{class:"plugin-uploader",drag:"","before-upload":E,"file-list":Object(a["unref"])(k),"show-file-list":!1,accept:".gz"},{default:Object(a["withCtx"])((function(){var e;return[null!==(e=w.value)&&void 0!==e&&e.name?(Object(a["openBlock"])(),Object(a["createElementBlock"])("p",b,Object(a["toDisplayString"])(w.value.name),1)):(Object(a["openBlock"])(),Object(a["createElementBlock"])("div",f,[Object(a["createVNode"])(n,{class:"icon-plus"},{default:Object(a["withCtx"])((function(){return[Object(a["createVNode"])(Object(a["unref"])(i["a"]),{class:"icon-plus"})]})),_:1}),Object(a["createElementVNode"])("span",p,Object(a["toDisplayString"])(j("dragFilePlaceholder")),1)]))]})),_:1},8,["file-list"]),Object(a["createElementVNode"])("p",v,Object(a["toDisplayString"])(j("uploadTip")),1),Object(a["createElementVNode"])("div",O,[Object(a["createVNode"])(c,{onClick:h},{default:Object(a["withCtx"])((function(){return[Object(a["createTextVNode"])(Object(a["toDisplayString"])(j("cancel","Base")),1)]})),_:1}),Object(a["createVNode"])(c,{type:"primary",loading:g.value,onClick:_},{default:Object(a["withCtx"])((function(){return[Object(a["createTextVNode"])(Object(a["toDisplayString"])(j("install")),1)]})),_:1},8,["loading"])])]})),_:1})])}}}),j=(n("95c5"),n("6b0d")),g=n.n(j);const h=g()(m,[["__scopeId","data-v-5677ec5e"]]);t["default"]=h},"6b0d":function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.default=(e,t)=>{const n=e.__vccOpts||e;for(const[r,a]of t)n[r]=a;return n}},"95c5":function(e,t,n){"use strict";n("cf2d")},"9ee5":function(e,t,n){"use strict";n.d(t,"a",(function(){return r}));var r=(e,t)=>{const n=e.__vccOpts||e;for(const[r,a]of t)n[r]=a;return n}},a90d:function(e,t,n){"use strict";n.d(t,"a",(function(){return l}));var r=n("7a23"),a=n("9ee5");const c=Object(r["defineComponent"])({name:"Plus"}),o={viewBox:"0 0 1024 1024",xmlns:"http://www.w3.org/2000/svg"},u=Object(r["createElementVNode"])("path",{fill:"currentColor",d:"M480 480V128a32 32 0 0 1 64 0v352h352a32 32 0 1 1 0 64H544v352a32 32 0 1 1-64 0V544H128a32 32 0 0 1 0-64h352z"},null,-1),i=[u];function s(e,t,n,a,c,u){return Object(r["openBlock"])(),Object(r["createElementBlock"])("svg",o,i)}var l=Object(a["a"])(c,[["render",s]])},c133:function(e,t,n){},cf2d:function(e,t,n){},de52:function(e,t,n){"use strict";n("c133")},e9b3:function(e,t,n){"use strict";n.d(t,"a",(function(){return l}));var r=n("7a23"),a=n("9ee5");const c=Object(r["defineComponent"])({name:"ArrowLeft"}),o={viewBox:"0 0 1024 1024",xmlns:"http://www.w3.org/2000/svg"},u=Object(r["createElementVNode"])("path",{fill:"currentColor",d:"M609.408 149.376 277.76 489.6a32 32 0 0 0 0 44.672l331.648 340.352a29.12 29.12 0 0 0 41.728 0 30.592 30.592 0 0 0 0-42.752L339.264 511.936l311.872-319.872a30.592 30.592 0 0 0 0-42.688 29.12 29.12 0 0 0-41.728 0z"},null,-1),i=[u];function s(e,t,n,a,c,u){return Object(r["openBlock"])(),Object(r["createElementBlock"])("svg",o,i)}var l=Object(a["a"])(c,[["render",s]])}}]);